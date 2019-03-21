#include <stdio.h>
#include <string.h>
#include "history.h"
#include "Malloc.h"
#include "LinkedQueue.h"

// TODO: Stuff in here to save and list history

queue_t history;

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
    for(int i = 0; new_line[i] != NULL; i++) {
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


queue_t *get_history() {
    return &history;
}

