#ifndef HASHMAPAPI_HASHTABLEAPI_H
#define HASHMAPAPI_HASHTABLEAPI_H

#include <stdio.h>
#include <stdlib.h>

typedef char* string;

typedef struct Node {
    string key;    //int that represents a piece of data in the table
    void* data;    //Pointer to generic data that is to be stored in the hash table
    struct Node* next;    //Pointer to the next Node if a collision is detected
} Node;

/**
 * Hash Table Structure
 */
typedef struct HTable {
    size_t size;    //Number that represents the size of the hash table
    Node** table;    //Array that contains all of the table nodes
    void (*destroyData)(Node* data);    //Function pointer to a function to delete a single piece of data from a hash table
    int (*hashFunction)(size_t tableSize, string key);    //Function pointer to a function to hash the data
    void (*printNode)(void* toBePrinted);    //Function pointer to a function that prints out a data element of the table
} HTable;

/**
 * Function to point the hash table to the appropriate functions. Allocates memory to the struct and table based on the size given.
 * @return pointer to the hash table
 * @param size size of the hash table
 * @param hashFunction function pointer to a function to hash the data
 * @param destroyData function pointer to a function to delete a single piece of data from the hash table
 * @param printNode function pointer to a function that prints out a data element of the table
 */
HTable* createTable(size_t size, int (*hashFunction)(size_t tableSize, string key), void (*destroyData)(Node* toDelete), void (*printNode)(void* toBePrinted));

/**
 * Function for creating a node for the hash table.
 * @pre Node must be cast to void pointer before being added
 * @post Node is valid and able to be added to the hash table
 * @param key string that represents the data
 * @param data is a generic pointer to any data type
 * @return returns a node for the hash table
 */
Node* createNode(string key, void* data);

/**
 * Deletes the entire hash table and frees memory of every element.
 * @pre Hash Table must exist.
 * @param hashTable pointer to hash table containing elements of data
 */
void destroyTable(HTable* hashTable);

/**
 * Inserts a Node in the hash table
 * @pre hashTable type must exist and have data allocated to it
 * @param hashTable pointer to the hash table
 * @param key string that represents the data
 * @param data pointer to generic data that is to be inserted into the list
 */
void insertData(HTable* hashTable, string key, void* data);

/**
 * Users call this function to insert a Node into the hash table.
 * It's meant as a wrapper for insertData so the users don't need to generate
 * the key when adding
 * @pre hashTable type must exist and have data allocated to it
 * @param hashTable pointer to the hash table
 * @param data pointer to generic data that is to be inserted into the list
 */
void add(HTable* hashTable, void* data);

/**
 * Function to remove a node from the hash table
 * @pre Hash table must exist and have memory allocated to it
 * @post Node at key will be removed from the hash table if it exists
 * @param hashTable pointer to the hash table struct
 * @param key string that represents a piece of data in the table
 */
void removeData(HTable* hashTable, string key);

/**
 * Function to return the data from the key given.
 * @pre The hash table exists and has memory allocated to it
 * @param hashTable pointer to the hash table containing data nodes
 * @param key string that represents a piece of data in the table
 * @return returns a pointer to the data in the hash table. Returns NULL if no match is found
 */
void* lookupData(HTable* hashTable, string key);

/**
 * Function to return the hashed value of the Node
 * @param size_t tableSize Size of the hash table
 * @param int key Key value
 * @return int Hashed value
 */
int hashNode(size_t tableSize, string key);

/**
 * Function to destroy a Node
 * @param Node data
 * @return void
 */
void destroyNodeData(Node* toDelete);

/**
 * Function to print a Node
 * @param void pointer toBePrinted
 * @return void
 */
void printNodeData(void* toBePrinted);

#endif //HASHMAPAPI_HASHTABLEAPI_H
