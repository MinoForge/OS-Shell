//
// Created by psgardner on 3/14/2019.
//
#include "Queue.h"

#ifndef OS_SHELL_HISTORY_H
    #define OS_SHELL_HISTORY_H

    #define HIST_SIZE 40

    void write_history(char*);
    queue_t *get_history();

#endif //OS_SHELL_HISTORY_H
