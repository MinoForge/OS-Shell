/**
 * This file contains code for a linkedlist implementation of a FIFO Queue.
 *
 * @author Peter Gardner
 * @author Wesley Rogers
 * @version February 27, 2019
 */
#include <stdio.h>
#include "LinkedQueue.h"
#include "Malloc.h"

typedef struct Node Node;
typedef struct LinkedQueue LinkedQueue;

/** This struct defines a one-directional node for the linked list. */
struct Node {
    char *data;
    Node *next;
};

/** This struct defines a linked list with a pointer for head and tail. */
struct LinkedQueue {
    Node *head;
    Node *tail;
    size_t size;
};

static Node *newNode(char*, Node*);
static void deleteNode(Node*);

static void linkedQueueEnqueue(queue_t *, char*);
static void linkedQueueDequeue(queue_t *);
static void linkedQueuePrint(queue_t *);
static size_t linkedQueueSize(queue_t *);
static char* linkedQueuePeek(queue_t *);

/**
 * Function for adding a new node to the tail of the queue. Can technically be used to insert anywhere with some work.
 * @param newData The data being put into the node.
 * @param nextNode A pointer to the node after the one being made.
 * @return A pointer to the newly created node.
 */
static Node *newNode(char *newData, Node* nextNode) {
    Node *node;
    node = Malloc(sizeof(Node));

    node->data = newData;
    node->next = nextNode;
    return node;
}

/**
 * Function to delete a given Node and all Nodes after it in a queue.
 * @param delNode The node to start deleting at.
 */
static void deleteNode(Node *delNode) {
    Node *temp, *del;
    temp = delNode;
    while(temp != NULL) {
        del = temp;
        temp = temp->next;
        free(del);
    }
}

/**
 * Function to create a new queue with a linked list implementation
 * @param self A pointer to a queue struct where this implementation will be put.
 */
void newLinkedQueue(queue_t *self) {
    LinkedQueue *queue_data;

    self->enqueue = linkedQueueEnqueue;
    self->dequeue = linkedQueueDequeue;
    self->print   = linkedQueuePrint;
    self->peek    = linkedQueuePeek;
    self->size    = linkedQueueSize;

    queue_data = (LinkedQueue *) Malloc(sizeof(LinkedQueue));
    queue_data->size = 0;
    queue_data->head = NULL;
    queue_data->tail = NULL;
    self->private_data = queue_data;
}

/**
 * Function to fully remove a linked list from a given queue struct.
 * @param queue A pointer to the given queue.
 */
void deleteLinkedQueue(queue_t *queue){
    LinkedQueue *internals;
    internals = queue->private_data;
    deleteNode(internals->head);
    free(internals);

    queue->enqueue = NULL;
    queue->dequeue = NULL;
    queue->peek    = NULL;
    queue->print   = NULL;
    queue->size    = NULL;
    queue->private_data = NULL;
}

/**
 * Function to add a piece of data to the end of the given queue.
 * @param queue A pointer to the given queue.
 * @param data The data to be added.
 */
static void linkedQueueEnqueue(queue_t *queue, char *data) {
    LinkedQueue *lQueue;
    lQueue = queue->private_data;
    if(lQueue->tail == NULL || lQueue->head == NULL) {
        lQueue->head = newNode(data, NULL);
        lQueue->tail = lQueue->head;
    } else {
        Node *temp = lQueue->tail;
        lQueue->tail = newNode(data, NULL);
        temp->next = lQueue->tail;
        if (lQueue->head->next == NULL) {
            lQueue->head = lQueue->tail;
        }
    }
    lQueue->size++;
}

/**
 * Function which returns the first element of data in the given queue.
 * @param queue The queue being looked at.
 * @return The integer in the first place of the queue.
 */
static char* linkedQueuePeek(queue_t *queue) {
    return ((LinkedQueue *)queue->private_data)->head->data;
}

/**
 * Function which removes the first element of data from the given queue.
 * @param queue The queue whose first element is being removed.
 */
static void linkedQueueDequeue(queue_t *queue) {
    LinkedQueue *lQueue;
    Node *temp;
    lQueue = queue->private_data;
    temp = lQueue->head->next;
    free(lQueue->head);
    lQueue->head = temp;
    if(lQueue->head == NULL){
        lQueue->tail = NULL;
    }
    lQueue->size--;
}

/**
 * Function which returns the current size of the given queue.
 * @param queue The queue whose size is being checked.
 * @return The size of the queue being checked.
 */
static size_t linkedQueueSize(queue_t *queue) {
    return ((LinkedQueue *)queue->private_data)->size;
}

/**
 * Function which traverses and prints out the contents of the given queue.
 * @param queue The queue whose contents are being printed out.
 */
static void linkedQueuePrint(queue_t *queue) {
    LinkedQueue *lQueue;
    Node *temp;
    if(queue->private_data != NULL) {
        lQueue = queue->private_data;
        temp = lQueue->head;
        /*printf("[");*/
        int i = 0;

        while (temp != NULL) {
            printf("%d: %s\n", i++, (temp->data));
            temp = temp->next;
            /*if(temp != NULL) {
                printf(", ");
            }*/
        }
    } else {
        printf("%s", "No history to print.\n");
    }

    /*printf("]\n");*/
}