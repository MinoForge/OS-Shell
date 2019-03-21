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
    /*                                                                          
     * TODO: Write code here that will list the content of the specified directory (or if no
     * directory was specified, the current directory).
     */                 
    DIR *dir = NULL;
    struct dirent *read = NULL;
    
    if(args[1] == NULL){
        dir = opendir("./");
    } else{
        dir = opendir(args[1]);

    }


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
        read = readdir(dir);
        while(read != NULL){
            printf("%s\n", read->d_name);
            read = readdir(dir);
        }

        free(dir);
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
    /*                                                                          
     * TODO: Write code here that will remove the specified list of files.  If no file list is
     * specified, print a usage message.
     */      
    int i = 1;
    
    if(args[1] == NULL){
        fprintf(stderr, "USAGE: rm <pathname> [addtl_files]\n");
    }else{
        while(args[i] != NULL){
            if((unlink(args[i])) < 0){
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
    int i = 1;
    int status = 0;
    struct stat stat_struct;
    struct utimbuf curr_time;
    curr_time.actime = time(NULL);
    curr_time.modtime = time(NULL);

    if(args[i] == NULL) {
        fprintf(stderr, "USAGE: touch <filename> [addtl_files]\n");
    }

    while(args[i] != NULL) {
        status = stat(args[i], &stat_struct);

        if(status == -1) {
            status = close(open(args[i], O_CREAT, 0644));
            if(status == -1) {
                fprintf(stderr, "touch: cannot touch \'%s\': Permission denied\n", args[i]);
            }
        }

        utime(args[i], &curr_time);
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
    size_t size;
    queue_t *hist = get_history();
    size_t curr_size = hist->size(hist);


    if (args[1] != NULL) {
        int num = atoi(args[1]);
        if (num < 0 || num > HIST_SIZE) {
            fprintf(stderr, "History argument out of range. Using maximum:\n");
            size = curr_size;
        } else {
            if (num > (int) curr_size) {
                size = curr_size;
            } else {
                size = (size_t) num;
            }
        }
        if(args[2] != NULL) {
            fprintf(stderr, "USAGE: history [0-%d]\n", HIST_SIZE);
        }
    } else {
        size = hist->size(hist);
    }



    hist->print(hist, size);

}
