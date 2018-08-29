#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "HashTableAPI.h"
#define DEBUG false

HTable* createTable(size_t size, int (*hashFunction)(size_t tableSize, string key), void (*destroyData)(Node* toDelete), void (*printNode)(void *toBePrinted)) {
    //Allocate space for the table and the inner-table
    HTable* newTable = malloc(sizeof(HTable));
    newTable->table = malloc(sizeof(Node) * size);

    //Initialize the inner table to NULL
    for (int i = 0; i < size; i++) {
        newTable->table[i] = NULL;
    }

    //Set remaining variables
    newTable->size = size;
    newTable->hashFunction = hashFunction;
    newTable->destroyData = destroyData;
    newTable->printNode = printNode;

    //Return the new table
    return newTable;
}

Node* createNode(string key, void* data) {
    //Allocate space for the new node
    Node* newNode = malloc(sizeof(Node));

    //Set variables of the node
    newNode->data = data;
    newNode->key = key;
    newNode->next = NULL;

    //Return the new node
    return newNode;
}

void destroyTable(HTable* hashTable) {
    if (hashTable == NULL) {
        return;
    }

    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i] != NULL) {
            //Free allocated Node
            free(hashTable->table[i]);
            hashTable->table[i] = NULL;
        }
    }

    //Free the array
    free(hashTable->table);
    hashTable->table = NULL;

    //Free the table
    free(hashTable);
    hashTable = NULL;
}

void insertData(HTable* hashTable, string key, void* data) {
    //Initialize variables
    int location = hashNode(hashTable->size, key);
    int i = 0;

    //Handle collision
    while (hashTable->table[location] != NULL && (i < hashTable->size)) {
        if(DEBUG)printf("Inside while loop\n");
        if (hashTable->table[i] == NULL) {
            if(DEBUG)printf("Inserting %s to hashTable->table[%d]\n", key, i);
            Node* toAdd = createNode(key, data);
            hashTable->table[i] = toAdd;
            return;
        }

        location = (location + 1) % hashTable->size;
        //Advance loop
        i++;
    }

    //Free slot to insert node
    if (hashTable->table[location] == NULL) {
        if(DEBUG)printf("Inserting %s to hashTable->table[%d]\n", key, location);
        Node* toAdd = createNode(key, data);
        hashTable->table[location] = toAdd;
    }
}

void add(HTable* hashTable, void* data) {
    ;
}

void removeData(HTable* hashTable, string key) {
    if (hashTable == NULL || key == NULL) {
        return;
    }

    //Rehash
    int location = hashNode(hashTable->size, key);

    //Set a Node to that location
    Node* temp = hashTable->table[location];
    //No Node found
    if (temp == NULL) {
        return;
    }

    int i = 0;
    //Handle collision
    while (temp != NULL && (i < hashTable->size)) {
        if (strcmp(temp->key, key) == 0) {
            //Delete Node
            //destroyNodeData(temp);
            //Delete Node from location
            free(temp);
            temp = NULL;
            return;
        }

        location = (location + 1) % hashTable->size;
        temp = hashTable->table[location];
        //Advance loop
        i++;
    }
}

void* lookupData(HTable* hashTable, string key) {
    if (hashTable == NULL || key == NULL) {
        return NULL;
    }

    //Rehash
    int location = hashNode(hashTable->size, key);

    //Set a Node to that location
    Node* temp = hashTable->table[location];
    //No Node found
    if (temp == NULL) {
        return NULL;
    }

    int i = 0;

    //Handle collision
    while (temp != NULL && (i < hashTable->size)) {
        if (strcmp(temp->key, key) == 0) {
            return temp;
        }

        location = (location + 1) % hashTable->size;
        temp = hashTable->table[location];
        //Advance loop
        i++;
    }
}

int hashNode(size_t tableSize, string key) {
    //djb2 hash function
    unsigned long hash = 5381;

    //Set a string pointer to the address of key and loop through until the end of the string
    for (string ptr = key; *ptr != '\0'; ptr++) {
        //Hash formula
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    //Return hash mod tableSize
    return hash % tableSize;
}

void destroyNodeData(Node* toDelete) {
    //Delete Node key
    //free(toDelete->key);
    //Delete Node data
    //free(toDelete->data);
    ;
}

void printNodeData(void* toBePrinted) {
    //Check if NULL
    if (toBePrinted == NULL) {
        return;
    }

    //Typecast to Node
    Node* temp = (Node*)(toBePrinted);
    if (temp->data && temp->key) {
        printf("Key: %s\nData: %s\n", temp->key, (string)(temp->data));
    }
}
