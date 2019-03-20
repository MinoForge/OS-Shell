#include <stdio.h>
#include <string.h>
#include "history.h"
#include "Malloc.h"
#include "LinkedQueue.h"

// TODO: Stuff in here to save and list history

queue_t history;

void write_history(char* new_line) {
    if(history.private_data == NULL) {
        newLinkedQueue(&history);
    }
    char* line = Calloc(strlen(new_line)+1, sizeof(char));
    strcpy(line, new_line);
    line[strlen(new_line)] = '\0';
    history.enqueue(&history, line);
    if(history.size(&history) > HIST_SIZE) {
        history.dequeue(&history);
    }
}


queue_t *get_history() {
    return &history;
}

