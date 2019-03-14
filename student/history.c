#include <stdio.h>
#include <string.h>
#include "history.h"
#include "Malloc.h"
#include "../queue/LinkedQueue.h"

// TODO: Stuff in here to save and list history

queue_t *history = NULL;

void write_history(char* new_line) {
    if(history == NULL) {
        newLinkedQueue(history);
    }
    history->enqueue(history, Calloc(strlen(new_line), sizeof(char)));
    if(history->size(history) > 40) {
        history->dequeue(history);
    }
}


queue_t *get_history() {
    return history;
}