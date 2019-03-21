/**
 * Header file which defines the queue struct, which ArrayQueue and LinkedQueue use heavily.
 *
 * @author Peter Gardner
 * @author Wesley Rogers
 * @version February 27, 2019
 */

#ifndef OPERATINGSYSTEMS_QUEUE_QUEUE_H
#define OPERATINGSYSTEMS_QUEUE_QUEUE_H

#include <stdlib.h>
typedef struct Queue queue_t;

typedef void (*enqueue_func)(queue_t*, char*);
typedef char* (*peek_func)(queue_t*);
typedef void (*dequeue_func)(queue_t*);
typedef size_t (*size_func)(queue_t*);
typedef void (*print_func)(queue_t*, size_t);

/**
 * The queue struct. Contains pointers to functions, and a pointer to private
 * data the queue implementation needs.
 */
struct Queue {
    void *private_data;

    enqueue_func enqueue;
    peek_func peek;
    dequeue_func dequeue;
    size_func size;
    print_func print;
};

#endif /* OPERATINGSYSTEMS_QUEUE_QUEUE_H */
