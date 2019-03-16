#ifndef SHELL_H
    #define SHELL_H
    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <signal.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <utime.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include "shellParser.h"
    #include "history.h"
    #include "LinkedQueue.h"


    /* Macros to test whether a process ID is a parent's or a child's. */
    #define PARENT_PID(pid) ((pid) > 0)
    #define CHILD_PID(pid)  ((pid) == 0)

    /* Function prototypes */
    char** prompt_and_read(void);
    pid_t  fork_wrapper(void);
    void   pipe_wrapper(int []);
    int    dup_wrapper(int);
    bool   is_special(char*);
    void   signal_handler(int);


    void   parse_args(char** , char** , int*);
    void   process_line(char **, int *, char **);
#endif


