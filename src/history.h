/**
 * Header file for history, defines useful constants and method signatures
 *
 * @author Peter Gardner
 * @author Caleb Dinehart
 * @version March 22, 2019
 */
#include "Queue.h"

#ifndef OS_SHELL_HISTORY_H
    #define OS_SHELL_HISTORY_H

    /** Size of history */
    #define HIST_SIZE 40

    /** A space string */
    #define SPACE " "

    /** Takes a new command and appends it to the history queue. If the history is full, it dequeues after enqueuing. */
    void write_history(char**);

    /** Gets a pointer to the history Queue.*/
    queue_t *get_history();

#endif //OS_SHELL_HISTORY_H
