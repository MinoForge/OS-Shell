#include "shell.h"

/*
 * append_redirection
 *
 * Redirects the standard output of this process to append to the file with the specified name.
 *
 * filename - the name of the file to which to append our output
 */
void append_redirection(char* filename) {
    /*
     * TODO:  Write code to cause the standard output of this process to be sent to a file with
     * the specified name.  The output should be appended to the file if the file already exists.
     */

    int fd = open(filename, O_APPEND | O_CREAT | O_WRONLY, 0644);
    if(fd == -1) {
        printf("Error opening file for writing.\n");
        fflush(stdout);
    }
    dup2(fd, 1);
    close(fd);

    
}

/*
 * stdout_redirection
 *
 * Redirects the standard output of this process to overwrite the file with the specified name.
 *
 * filename - the name of the file which to overwrite
 */
void stdout_redirection(char* filename) {
    /*
     * TODO:  Write code to cause the standard output of this process to be sent to a file with
     * the specified name.  If the file already exists, its contents should be truncated before
     * this process writes to the file.
     */

    
    int fd = open(filename, O_TRUNC | O-CREAT | O_WRONLY, 0644);
    if(fd == -1) {
        printf("Error opening file for writing.");
    }
    dup2(fd,1);
    close(fd);
    
}
/*
 * stderr_redirection
 *
 * Redirects the standard error of this process to overwrite the file with the specified name.
 *
 * filename - the name of the file which to overwrite
 */
void stderr_redirection(char* filename) {
    /*
     * TODO:  Write code to cause the standard error of this process to be sent to a file with the
     * specified name.  If the file already exists, its contents should be truncated before this
     * process writes to the file.
     */

    close(2);
    int fd = open(filename, O_TRUNC |  O-CREAT | O_WRONLY, 0644);
    if(fd == -1) {
        printf("Error opening file for writing.");
    }
    dup(fd,2);
    close(2);
}

/*
 * stdout_stderr_redirection
 *
 * Redirects the standard output AND standard error of this process to overwrite the file with the
 * specified name.
 *
 * filename - the name of the file which to overwrite
 */
void stdout_stderr_redirection(char* filename) {
    /*
     * TODO:  Write code to cause the standard output and standard error of this process to be
     * sent to a file with the specified name.  If the file already exists, its contents should be
     * truncated before this process writes to the file.
     */

    int fd = open(filename, O_TRUNC |  O-CREAT | O_WRONLY, 0644);
    if(fd == -1) {
        printf("Error opening file for writing.");
    }
    dup2(fd, 2);
    dup2(fd, 1);
    close(1);
    close(2);
    

}
/*
 * stdin_redirection
 *
 * Redirects the standard input to this process from the file with the specified name.
 *
 * filename - the name of the file from which to read as standard input.
 */
void stdin_redirection(char* filename) {
    /*
     * TODO:  Write code to cause the standard input of this process to be read from a file with
     * the specified name.
     */

    int fd = open(filename, O_RDONLY);
    if(fd == -1) {
        printf("Error opening file for reading.\n");
    }
    dup2(fd, 0);
    close(0);
}

