/**
 * Header file for redirection.
 *
 * @author Peter Gardner
 * @author Caleb Dinehart
 * @version March 22, 2019
 */
#ifndef REDIRECT_H
   #define REDIRECT_H
    void   append_redirection(char*);
    void   stdout_redirection(char*);
    void   stderr_redirection(char*);
    void   stdout_stderr_redirection(char*);
    void   stdin_redirection(char*);
#endif
