/**
 * Header file for builtin shell functions.
 *
 * @author Peter Gardner
 * @author Caleb Dinehart
 * @version March 22, 2019
 */
#ifndef BUILTIN_H
    #define BUILTIN_H
    void   do_pipe(char** , char** , int*);
    void   do_file_list(char**);
    void   do_file_remove(char**);
    void   do_touch(char**);
    void   do_history(char**);
#endif
