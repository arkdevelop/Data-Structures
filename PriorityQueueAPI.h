#ifndef QUEUEAPI_H
#define QUEUEAPI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedListAPI.h"

/**
 * Stores basic queue information
 */
typedef struct queue {
    List list;
    int count;
} Queue;

/**
 * createQueue: Creates a queue with the appropriate specifications
 * @param printFunction function pointer to print a single node from the queue
 * @param deleteFunction function pointer to delete a single piece of data from the queue
 * @param compareFunction function pointer to compare two nodes of the queue
 * @return the queue struct
 */
Queue* createQueue(char* (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (compareFunction)(const void* first, const void* second));

/**
 * destroy: Destroys a queue
 * @param Queue* queue
 * @return void
 */
void destroy(Queue* queue);

/**
 * insert: Inserts into a queue
 * @param Queue* queue
 * @param void* toBeAdded
 * @return void
 */
void insert(Queue* queue, void* toBeAdded);

/**
 * pop: Removes the first element of a queue
 * @param Queue* queue
 * @return void
 */
void pop(Queue* queue);

/**
 * peek: Looks at the head of a queue and returns the data
 * @param Queue* queue
 * @return void* data of the head of the queue
 */
void* peek(Queue* queue);

/**
 * deleteNode: Deletes a node from a queue
 * @param Queue* queue
 * @param void* toBeDeleted
 * @return void
 */
void deleteNode(Queue* queue, void* toBeDeleted);

/**
 * isEmpty: Checks if the queue is empty
 * @param Queue* queue
 * @return 0 on queue empty, else 1
 */
int isEmpty(Queue* queue);

#endif //QUEUEAPI_H
