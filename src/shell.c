/*
 * shell.c
 *
 * Written by Dr. William Kreahling
 *            Department of Mathematics and Computer Science
 *            Western Carolina University
 *
 * An implementation of a simple UNIX shell.  This program supports:
 *
 *     - Running processes
 *     - Redirecting standard output (>)
 *     - Redirecting standard input (<)
 *     - Appending standard output to a file (>>)
 *     - Redirecting both standard output and standard input (&>)
 *     - Creating process pipelines (p1 | p2 | ...)
 *     - Interrupting a running process (i.e., Ctrl-C)
 *     - A built-in version of the 'ls' command
 *     - A built-in version of the 'rm' command
 *     - A built-in version of the 'touch' command
 *     - A built-in 'history' list
 *
 * Among the many things it does _NOT_ support are:
 *
 *     - Environment variables
 *     - Appending standard error to a file (2>>)
 *     - Appending both standard output and standard input (2&>)
 *     - Backgrounding processes (p1&)
 *     - Unconditionally chaining processes (p1;p2)
 *     - Conditionally chaining processes (p1 && p2 or p1 || p2)
 *     - re-executing history commands
 *
 * Keep in mind that this program was written to be easily understood/modified for educational
 * purposes.  The author makes no claim that this is the "best" way to solve this problem.
 */
#include "shell.h"
#include "redirect.h"
#include "builtin.h"
#include "shellParser.h"

/* Macros to test whether a process ID is a parent's or a child's. */
#define PARENT_PID(pid) ((pid) > 0)
#define CHILD_PID(pid)  ((pid) == 0)


/*
 * A global variable representing the process ID of this shell's child.
 * When the value of this variable is 0, there are no running children.
 */
static pid_t childPid = 0;


void signal_handler(int sig){
    if(sig != SIGINT) {
        printf("Intercepted SIGINT, but was not passed SIGINT."); //Added to make -Wall happy
    }
    if(childPid != 0){

        kill(childPid, SIGKILL);
        childPid = 0;
    }
}



/*
 * Entry point of the application
 */
int main(void) {
    char** line;

    /*
     * TEST  TODO:  Define a signal handler function below, add a function prototype above, and call the
     * 'signal' system call here to put that handler in place for the SIGINT signal.  (The SIGINT
     * signal is what gets sent to a process when you hit Ctrl-C).  The implementation of your
     * signal hander should deliver the received signal to the process with pid 'childPid'
     * (above).  Note that when 'childPid' contains 0, the signal should be ignored.
     */
    signal(SIGINT, signal_handler);

    /* Read a line of input from the keyboard */
    line = prompt_and_read();
    
    /* While the line was blank or the user didn't type exit */
    while (line[0] == NULL || (strcmp(line[0], "exit") != 0)) {
        int lineIndex = 0; /* An index into the line array */

        /* Ignore blank lines */
        if (line[lineIndex] != NULL) {
            int   status;
            char* args[MAX_ARGS]; /* A process's arguments */

            /* Dig out the arguments for a single process */
            parse_args(args, line, &lineIndex);

            /* TODO: Somewhere here remember commands executed*/
            write_history(*line);

            /* Determine which command we are running*/
            if (strcmp(args[0], "ls") == 0) {
                do_file_list(args);
            } else if (strcmp(args[0], "touch") == 0) {
                do_touch(args);
            } else if (strcmp(args[0], "rm") == 0) {
                do_file_remove(args);
            } else if (strcmp(args[0], "history") == 0) {
                do_history(args);
            } else {
                /* Fork off a child process */
                childPid = fork_wrapper();


                if (CHILD_PID(childPid)) {
                    /* The child shell continues to process the command line */
//                    printf("%s", "Child started");
                    process_line(line, &lineIndex, args);
                } else {

                    /*
                     * TODO:  Write code here to wait for the child process to die.  When the
                     * child finally does die, include a printf that prints a message like:
                     *
                     *            "Child 123 exited with status 0"
                     *
                     *        Where 123 here is the process id of the child and 0 is the exit
                     *        status of that process.
                     */
                    status = 0;
                    pid_t reaped = wait(&status);
                    printf("Child %d exited with status %d\n", (int)reaped, status);
                    
                   

                }
            }
        }

        /* Read the next line of input from the keyboard */
        line = prompt_and_read();
    }

    /* TODO Added to clean up history */
    deleteLinkedQueue(get_history());
//    free(get_history());

    /* User must have typed "exit", time to gracefully exit. */
    return 0;
}


/*
 * process_line
 *
 * This processes thr remainder of a line read in from the user.  This processing can include
 * append redirection, stderr redirection, etc.  Note that this function operates recursively; it
 * breaks off a piece associated with a process until it gets to something "special", decides what
 * to do with that "special" thing, and then calls itself to handle the rest.  The base case of the
 * recursion is when the end of the 'line' array is reached (i.e., when line[*lineIndex] == NULL).
 *
 * line      - An array of pointers to string corresponding to ALL of the tokens entered on the
 * command line.
 * lineIndex - A pointer to the index of the next token to be processed
 * args      - A NULL terminated array of string corresponding to the
 *             arguments for a process (i.e., stuff that was already parsed
 *             off of line).
 */
void process_line(char **line, int *lineIndex, char **args) {
    if (line[*lineIndex] == NULL) { /* Base case -- nothing left in line */
        /*
         * TEST?? TODO:  We've read the end of a command line.  Here args is an array of strings
         * corresponding to the command line arguments of a process that needs to get started.
         * Replace the call to the 'exit' system call below with code to replace this in-memory
         * process image with an instance of the specified program.
         */
        if(execvp(args[0], args)) {
            _exit(1);
        }

    } else if (strcmp(line[*lineIndex], ">>") == 0) {
        (*lineIndex)++;
        append_redirection(line[*lineIndex]);

        (*lineIndex)++;
        process_line(line, lineIndex, args);

    } else if (strcmp(line[*lineIndex], "2>") == 0) {
        (*lineIndex)++;
        stderr_redirection(line[*lineIndex]);

        (*lineIndex)++;
        process_line(line, lineIndex, args);

    } else if (strcmp(line[*lineIndex], "&>") == 0) {
        (*lineIndex)++;
        stdout_stderr_redirection(line[*lineIndex]);

        (*lineIndex)++;
        process_line(line, lineIndex, args);

    } else if (strcmp(line[*lineIndex], ">") == 0) {
        (*lineIndex)++;
        stdout_redirection(line[*lineIndex]);

        (*lineIndex)++;
        process_line(line, lineIndex, args);

    } else if (strcmp(line[*lineIndex], "<") == 0) {
        (*lineIndex)++;
        stdin_redirection(line[*lineIndex]);

        (*lineIndex)++;
        process_line(line, lineIndex, args);

    } else if (strcmp(line[*lineIndex], "|") == 0) {
        (*lineIndex)++;
        do_pipe(args, line, lineIndex);
        /* do_pipe() calls process_line() only in some cases */
    }
}

/*
 * do_pipe
 *
 * Implements a pipe between two processes.
 *
 * p1Args    - The arguments for the left-hand-side command.
 * line      - An array of pointers to string corresponding to ALL of the
 *             tokens entered on the command line.
 * lineIndex - A pointer to the index of the next token to be processed.
 *             This index should point to one element beyond the pipe
 *             symbol.
 */
void do_pipe(char** p1Args, char** line, int* lineIndex) {
    int   pipefd[2]; /* Array of integers to hold 2 file descriptors. */
    pid_t pid;       /* PID of a child process */

    /*
     * TODO: Write code here that will create a pipe -- a unidirectional data channel that can be
     * used for interprocess communication.
     */
    pipe(pipefd);

    /* Fork the current process */
    pid = fork_wrapper();

    if (CHILD_PID(pid)) { /* Child -- will execute left-hand-side process */
        /*
         * TODO:  This process will handles the left-hand-side of this pipe.  Write code here to
         * connect this processes standard output stream to the output side of the pipe in pipefd.
         * Close any unnecessary file descriptors.
         */
//        int out = dup(1);
        /* Might change to STDOUT_FILENO */
        close(1);
        dup2(pipefd[0], 1);      
        





        /*
         * TODO:  We're ready to start our pipeline!  Replace the call to the 'exit' system call
         * below with code to replace this in-memeory process image with an instance of the
         * specified program.  (Here, in p1Args)
         */
        if(execvp(p1Args[0], p1Args)) {
            _exit(2);
        }
        
        
        
//        close(1);
//        dup2(out, 1);
//        close(out);
//        _exit(1);

    } else {  /* Parent will keep going */
        char* args[MAX_ARGS];

        /*
         * TODO:  This process will handles the right-hand-side of this pipe.  Write code here to
         * connect this processes standard input stream to the input side of the pipe in pipefd.
         * Close any unnecessary file descriptors.
         */
//        int in = dup(0);
        /* Might change to STDOUT_FILENO */
        close(0);
        dup2(pipefd[1], 0);
        





        /* Read the args for the next process in the pipeline */
        parse_args(args, line, lineIndex);

        /* And keep going... */
        process_line(line, lineIndex, args);
    }
}

/*
 * parse_args
 *
 * Parse the command line, stopping at a special symbol of the end of the line.
 *
 * args      - The array to populate with arguments from line
 * line      - An array of pointers to string corresponding to ALL of the
 *             tokens entered on the command line.
 * lineIndex - A pointer to the index of the next token to be processed.
 *             This index should point to one element beyond the pipe
 *             symbol.
 */
void parse_args(char** args, char** line, int* lineIndex) {
    int i;

    for (i = 0;    line[*lineIndex] != NULL
                && !is_special(line[*lineIndex]); ++(*lineIndex), ++i) {
        args[i] = line[*lineIndex];
    }
    args[i] = NULL;
}

/*
 * prompt_and_read
 *
 * A simple wrapper that displays a prompt and reads a line of input from the user.
 *
 * Returns a pointer to an array of strings where each element in the array corresponds to a token
 * from the input line.
 */
char** prompt_and_read(void) {
    printf("(%d) $ ", getpid());
    return getArgList();
}

/*
 * fork_wrapper
 *
 * A simple wrapper around the 'fork' system call that attempts to invoke fork and on failure,
 * prints an appropriate message and terminates the process.
 */
pid_t fork_wrapper(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        _exit(2);
    }

    return pid;
}

/*
 * pipe_wrapper
 *
 * A simple wrapper around the 'pipe' system call that attempts to invoke pipe and on failure,
 * prints an appropriate message and terminates the process.
 */
void pipe_wrapper(int pipefds[]) {
    /*                                                                          
     * TODO: Write code here that will create a pipe -- a unidirectional data channel that can
     * be used for interprocess communication. Check the return value of pipe -- if it
     * is less than 0, use perror() to print an error message and the _exit system call to
     * terminate the program.                                             
     */                                                                         
    int p = pipe(pipefds);
    
    if(p < 0){
        perror("pipe");
        _exit(1);
    }
    



}

/*
 * dup_wrapper
 *
 * A simple wrapper around the 'dup' system call that attempts to invoke pipe and on failure,
 * prints an appropriate message and terminates the process.
 */
int dup_wrapper(int oldfd) {
    /*                                                                          
     * TODO: Write code here that will duplicate a file descriptor and return a new one, assuming
     * nothing has gone wrong.  Check the return value of dup -- if it is less than 0, use perror()
     * to print an error message and the _exit system call to terminate the program.
     */                                                                         
    int newfd;
    if((newfd = dup(oldfd)) < 0){
        perror("dup");
        _exit(1);
    }
    return newfd;

}

/*
 * is_special
 *
 * Returns true if the specified token is "special" (i.e., is an operator like >, >>, |, <); false
 * otherwise.
 */
bool is_special(char* token) {
    return    (strlen(token) == 1 && strchr("<>|!", token[0]) != NULL)
           || (strlen(token) == 2 && strchr(">",    token[1]) != NULL);
}

