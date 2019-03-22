/**
 * Header file for LinkedQueue.
 *
 * Originally written by:
 * @author Peter Gardner
 * @author Wesley Rogers
 * @version February 27, 2019
 *
 * Used, but unmodified by:
 * @author Peter Gardner
 * @author Caleb Dinehart
 * @modified March 22, 2019
 */

#ifndef OPERATINGSYSTEMS_QUEUE_LINKEDQUEUE_H
#define OPERATINGSYSTEMS_QUEUE_LINKEDQUEUE_H

#include "Queue.h"

/** Initializes a new LinkedQueue into the given queue struct. */
void newLinkedQueue(queue_t*);

/** Destroys the LinkedQueue inside the given queue struct and nulls out the struct. */
void deleteLinkedQueue(queue_t*);




#endif /* OPERATINGSYSTEMS_QUEUE_LINKEDQUEUE_H */
