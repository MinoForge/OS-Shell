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
        if(dir == NULL){
            printf("The directory %s does not exist\n", args[1]);
        }
    }
    
    read = readdir(dir);
    while(read != NULL){
        printf("%s\n", read->d_name);
        read = readdir(dir);
    }

    free(dir);

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
        printf("USAGE: rm <pathname> [addtl_files]\n");
    }else{
        while(args[i] != NULL){
            if((unlink(args[i])) < 0){
                printf("\"%s\" does not exist.", args[i]);
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
    //TODO set curr_time
    curr_time.actime = UTIME_NOW;
    curr_time.modtime = UTIME_NOW;

    if(args[i] == NULL) {
        printf("USAGE: touch <filename> [addtl_files]\n");
    }

    while(args[i] != NULL) {
        status = stat(args[i], &stat_struct);

        if(status == -1) {
            status = close(open(args[i], O_CREAT));
            if(status == -1) {
                printf("You do not have permission to create files in this directory.\n");
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
    if(args[1] != NULL) {
        printf("Ignoring extraneous arguments to history():\n");
    }
    queue_t *hist = get_history();
    hist->print(hist);

}


//TODO Make a main, that picks the right thing?
