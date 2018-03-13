/**
 * @file PriorityQueueAPI.c
 * @author Alexander R-K
 * @date 01/09/2017
 * @brief File containing the functions of a priority queue
 */

//Includes
#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueueAPI.h"
#include "LinkedListAPI.h"

Queue* createQueue(char* (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (*compareFunction)(const void* first, const void* second)) {
    Queue* queue = malloc(sizeof(Queue));
    List list = initializeList(printFunction, deleteFunction, compareFunction);
    queue->list = list;
    queue->count = 0;

    return queue;
}

void destroy(Queue* queue) {
    if (queue == NULL) {
        return;
    }

    while (queue->count != 0) {
        pop(queue);
	    queue->count--;
    }

    free(queue);
}

void insert(Queue* queue, void* toBeAdded) {
    insertSorted(&queue->list, toBeAdded);
    queue->count++;
}

void pop(Queue* queue) {
    if (queue == NULL) {
        return;
    }

    if (isEmpty(queue) == 1) {
        deleteDataFromList(&queue->list, queue->list.head);
        queue->count--;
    }
}

void* peek(Queue* queue) {
    if (queue == NULL) {
        return NULL;
    }

    if (isEmpty(queue) == 1) {
        return getFromFront(queue->list);
    }

    return NULL;
}

void deleteNode(Queue* queue, void* toBeDeleted) {
    if (queue == NULL) {
        return;
    }

    if (isEmpty(queue) == 1) {
        deleteDataFromList(&queue->list, toBeDeleted);
        queue->count--;
    }
}

int isEmpty(Queue* queue) {
    if (queue->count == 0) {
        return 0;
    }
    else {
        return 1;
    }
}
