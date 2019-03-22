/**
 * Implementations of the four built in functions of our shell.
 *
 * @author Peter Gardner
 * @author Caleb Dinehart
 * @version March 22, 2019
 */
#include <time.h>
#include <errno.h>
#include <asm/errno.h>
#include "shell.h"
    
/**
 * do_file_list
 *
 * Implements a built-in version of the 'ls' command.
 *
 * args - An array of strings corresponding to the command and its arguments.
 *        If args[1] is NULL, the current directory (./) is assumed; otherwise
 *        it specifies the directory to list.
 */
void do_file_list(char** args) { 
    
    DIR *dir = NULL;
    struct dirent *read = NULL;
    
    /*Check if a directory was specified, then ope the directory with the 'opendir' system call*/
    if(args[1] == NULL){
        dir = opendir("./");
    } else{
        dir = opendir(args[1]);
    }

    /* Code to check for errors */
    if(dir == NULL){
        if(errno == ENOENT) {
            fprintf(stderr, "ls: cannot access \'%s\': No such file or directory\n", args[1]);
        } else if(errno == EACCES) {
            fprintf(stderr, "ls: cannot open directory \'%s\': Permission denied\n", args[1]);
        } else if(errno == ENOTDIR) {
            printf("%s\n", args[1]);
        } else {
            fprintf(stderr, "ls: Unimplemented error: see 'man opendir' for possibilities\n");
        }
    } else {
        /* Use the 'readdir' system call to move through the files in the opened directory */
        read = readdir(dir);
        while(read != NULL){
            /* print the file name */
            printf("%s\n", read->d_name);
            read = readdir(dir);
        }

        closedir(dir);
    }


}

/**
 * do_file_remove
 *
 * Implements a built-in version of the 'rm' command.q
 *
 * args - An array of strings corresponding to the command and its arguments.
 *        args[0] is "rm", additional arguments are in args[1] ... n.
 *        args[x] = NULL indicates the end of the argument list.
 */
void do_file_remove(char** args) {
          
    int i = 1;
    
    if(args[1] == NULL){
        fprintf(stderr, "USAGE: rm <pathname> [addtl_files]\n");
    }else{
        while(args[i] != NULL){
            /* Using the 'unlink' system call to remove the files from the directory */
            if((unlink(args[i])) < 0){
                /* Error checking */
                if(errno == ENOENT) {
                    fprintf(stderr, "rm: cannot remove \'%s\': No such file or directory\n", args[i]);
                } else if(errno == EACCES) {
                    fprintf(stderr, "rm: cannot remove \'%s\': Permission denied\n", args[1]);
                } else {
                    fprintf(stderr, "rm: Unimplemented error\n");
                }
            }
            i++;
        }
        
    }






}
/**
 * do_touch
 *
 * Implements a built-in version of the 'touch' command.
 *
 * args - An array of strings corresponding to the command and its arguments.
 *        args[0] is "touch", additional arguments are in args[1] ... n.
 *        args[x] = NULL indicates the end of the argument list.
 */
void do_touch(char** args) {
    /*                                                                          
     * TODO: Write code here that will modify the access time of a file(s) if it exists, or create
     * the file(s) if it/they does not exist.  If no file list is specified, print a usage message.
     */                                                                         
    int i = 1; /* The first argument to touch */
    int status = 0;
    struct stat stat_struct;

    /* Struct to hold the current time. */
    struct utimbuf curr_time;
    curr_time.actime = time(NULL);
    curr_time.modtime = time(NULL);

    if(args[i] == NULL) { /* Usage */
        fprintf(stderr, "USAGE: touch <filename> [addtl_files]\n");
    }

    while(args[i] != NULL) { /* loop for all files given */
        status = stat(args[i], &stat_struct);

        if(status == -1) { /* If file does not exist, create the file. */
            status = close(open(args[i], O_CREAT, 0644));
            if(status == -1) { /* If file could not be created */
                fprintf(stderr, "touch: cannot touch \'%s\': Permission denied\n", args[i]);
            }
        }

        utime(args[i], &curr_time); /* Set modified time to current. */
        i++;
    }






}
/**
 * do_history
 *
 * Implements a built-in version of the 'history' command. This will just list the command in the
 * form:
 *  0: command
 *  1: command
 *  2: command
 *
 * args - An array of strings corresponding to the command and its arguments.
 *        args[0] is "history", additional arguments are in args[1] ... n.
 *        args[x] = NULL indicates the end of the argument list.
 */
void do_history(char** args) {
        /*
         * TODO: Write code here that will print the last n commands executed via this shell.
         */
    /** Variables for reading the history */
    size_t size;
    queue_t *hist = get_history();
    size_t curr_size = hist->size(hist);


    if (args[1] != NULL) { /* If they give us at least one argument */
        int num = atoi(args[1]); /* Tries to get an integer out of the first arg */
        if (num < 0 || num > HIST_SIZE) { /* If num out of range */
            fprintf(stderr, "History argument out of range. Using maximum:\n");
            size = curr_size;
        } else { /* If num in range */
            if (num > (int) curr_size) {  /*num larger than how many elements are in history: use current size. */
                size = curr_size;
            } else { /* num smaller than current size */
                size = (size_t) num;
            }
        }
        if(args[2] != NULL) { /* Gave too many arguments */
            fprintf(stderr, "USAGE: history [0-%d]\n", HIST_SIZE);
        }
    } else { /* No arguments given */
        size = hist->size(hist);
    }

    hist->print(hist, size); /* Print the history. Modified from queues original print. */

}
