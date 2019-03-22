#include <stdio.h>
#include <string.h>
#include "history.h"
#include "Malloc.h"
#include "LinkedQueue.h"

/**
 * Allows writing lines to a queue for purposes of storing commands to the shell.
 *
 * @author Peter Gardner
 * @author Caleb Dinehart
 * @version March 22, 2019
 */

// TODO: Stuff in here to save and list history

/** A queue to hold the history of commands sent to the shell. */
static queue_t history;

/**
 * Takes a new command and appends it to the history queue. If the history is full, it dequeues after enqueuing.
 * @param new_line An array of pointers to string corresponding to ALL of the tokens entered on the
 * command line. Terminated with a NULL line.
 */
void write_history(char** new_line) {

    if(history.private_data == NULL) {
        newLinkedQueue(&history);
    }
    size_t size = 0;
    int i;
    for(i = 0; new_line[i] != NULL; i++) {
        size = size + strlen(new_line[i]);
    }
    char* line = Calloc(size + i, sizeof(char));
    char* target = line;
    for(i = 0; new_line[i] != NULL; i++) {
        strcat(target, new_line[i]);
        target += strlen(new_line[i]);
        if(new_line[i+1] != NULL) {
            strcat(target, SPACE);
            target++;
        }
    }
    *(target) = '\0';

    history.enqueue(&history, line);
    if(history.size(&history) > HIST_SIZE) {
        history.dequeue(&history);
    }
}

/**
 * Gets a pointer to the history Queue.
 * @return a pointer to the history Queue.
 */
queue_t *get_history() {
    return &history;
}

