#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BinarySearchTreeAPI.h"
#define DEBUG false

TreeNode* createTreeNode(TreeDataPtr data) {
    //Create the treeNode, initialize values, then return the dynamically created treeNode
    TreeNode* toReturn = malloc(sizeof(TreeNode));
    toReturn->data = data;
    toReturn->left = NULL;
    toReturn->right = NULL;
    toReturn->parent = NULL;

    return toReturn;
}

Tree* createBinTree(CompareFunc compare, DeleteFunc del, PrintFunc print) {
    //Create the tree, initialize values, then return the dynamically created tree
    Tree* toReturn = malloc(sizeof(Tree));
    toReturn->root = NULL;
    toReturn->count = 0;
    toReturn->printFunc = print;
    toReturn->deleteFunc = del;
    toReturn->compareFunc = compare;

    return toReturn;
}

void destroyBinTree(Tree* toDestroy) {
    //Check if the tree is NULL, if it is, there's nothing to delete
    if (toDestroy == NULL) {
        return;
    }
    destroyBinTreeSub(toDestroy->root, toDestroy->deleteFunc);
    free(toDestroy);
}

void destroyBinTreeSub(TreeNode* tempNode, DeleteFunc del) {
    if (tempNode == NULL) {
        return;
    }

    destroyBinTreeSub(tempNode->left, del);
    destroyBinTreeSub(tempNode->right, del);
    del(tempNode->data);
}

void addToTree(Tree* theTree, TreeDataPtr data) {
    if (theTree->root == NULL) {
        theTree->root = insert(theTree->root, data, theTree->compareFunc);
        theTree->count++;
    }
    else {
        insert(theTree->root, data, theTree->compareFunc);
        theTree->count++;
    }
}

TreeNode* insert(TreeNode* treeNode, TreeDataPtr data, CompareFunc compare) {
    //Base case: Tree is empty - Create node with data
    if (treeNode == NULL) {
        treeNode = createTreeNode(data);
    }

    //Recurse to the right if the treeNode is more than the current data
    if (compare(treeNode->data, data) < 0) {
        treeNode->right = insert(treeNode->right, data, compare);
    }
    //Recurse to the left if the treeNode is less than the current data
    else if (compare(treeNode->data, data) > 0) {
        treeNode->left = insert(treeNode->left, data, compare);
    }

    //Return
    return treeNode;
}

void removeFromTree(Tree* theTree, TreeDataPtr data) {
    TreeNode* tempNode = createTreeNode(data);
    TreeNode* returnedNode = removeFromTreeSub(tempNode, data, theTree->compareFunc, theTree->deleteFunc);

    if (returnedNode == NULL) {
        printf("Successfully deleted\n");
    }
    else {
        printf("Unsuccessful deletion attempt\n");
    }

}

TreeNode* removeFromTreeSub(TreeNode *tempNode, TreeDataPtr data, CompareFunc compare, DeleteFunc del) {
    if (tempNode == NULL) {
        return tempNode;
    }
    else if (compare(data, tempNode->data) < 0) {
        removeFromTreeSub(tempNode->left, data, compare, del);
    }
    else if (compare(data, tempNode->data) > 0) {
        removeFromTreeSub(tempNode->right, data, compare, del);
    }
    else {
        if (isLeaf(tempNode) == 1) {
            del(tempNode->data);
            free(tempNode);
            //tempNode = NULL;
        }
        else if (hasOneChild(tempNode) == 1) {
            if (tempNode->left == NULL) {
                TreeNode *temp = tempNode;
                tempNode = tempNode->right;
                del(temp->data);
                free(temp);
                //temp = NULL;
            }
            else {
                TreeNode *temp = tempNode;
                tempNode = tempNode->left;
                del(temp->data);
                free(temp);
                //temp = NULL;
            }
        }
        else {
            TreeNode *temp = findMin(tempNode->right);
            tempNode->data = temp->data;
            removeFromTreeSub(tempNode->right, tempNode->data, compare, del);
        }
    }
    return tempNode;
}

TreeDataPtr findInTree(Tree* theTree, TreeDataPtr data) {
    //Send data to recursive function for searching
    TreeNode* returned = findInTreeSub(theTree->root, data, theTree->compareFunc);

    //Check if the returned value is NULL. If not NULL, return the data
    if (returned != NULL) {
        return returned->data;
    }
    else {
        return NULL;
    }
}

TreeNode* findInTreeSub(TreeNode* treeNode, TreeDataPtr data, CompareFunc compare) {
    //Base case: Check if the treeNode is the data - if it is, return it
    if (treeNode == NULL || compare(treeNode->data, data) == 0) {
        return treeNode;
    }
    //Recurse to the right if the treeNode is more than the current data
    else if (compare(treeNode->data, data) < 0) {
        return findInTreeSub(treeNode->right, data, compare);
    }
    //Recurse to the left if the treeNode is less than the current data
    else {
        return findInTreeSub(treeNode->left, data, compare);
    }
}

TreeDataPtr getRootData(Tree* theTree) {
    if (theTree->root != NULL) {
        return theTree->root->data;
    }
    else {
        return NULL;
    }
}

void printInOrder(Tree* theTree, PrintFunc printData) {
    printInOrderSub(theTree, theTree->root, printData);
}

void printInOrderSub(Tree* theTree, TreeNode* treeNode, PrintFunc printData) {
    if (treeNode == NULL) {
        return;
    }

    printInOrderSub(theTree, treeNode->left, printData);
    printData(treeNode->data);
    printInOrderSub(theTree, treeNode->right, printData);
}

void printPreOrder(Tree* theTree, PrintFunc printData) {
    printPreOrderSub(theTree, theTree->root, printData);
}

void printPreOrderSub(Tree* theTree, TreeNode* treeNode, PrintFunc printData) {
    if (treeNode == NULL) {
        return;
    }

    printData(treeNode->data);
    printPreOrderSub(theTree, treeNode->left, printData);
    printPreOrderSub(theTree, treeNode->right, printData);
}

void printPostOrder(Tree* theTree, PrintFunc printData) {
    printPostOrderSub(theTree, theTree->root, printData);
}

void printPostOrderSub(Tree* theTree, TreeNode* treeNode, PrintFunc printData) {
    if (treeNode == NULL) {
        return;
    }

    printPostOrderSub(theTree, treeNode->left, printData);
    printPostOrderSub(theTree, treeNode->right, printData);
    printData(treeNode->data);
}

int isTreeEmpty(Tree* theTree) {
    if (theTree->root == NULL) {
        //Return 1 because theTree is empty (It does not have a root node)
        return 1;
    }
    else {
        //Return 0 because theTree is not empty (It has at least one node)
        return 0;
    }
}

int isLeaf(TreeNode* treeNode) {
    if (treeNode->left == NULL && treeNode->right == NULL) {
        //Return 1 because treeNode is a leaf
        return 1;
    }
    else {
        //Return 0 because treeNode is not a leaf
        return 0;
    }
}

int hasTwoChildren(TreeNode* treeNode) {
    if (treeNode->left != NULL && treeNode->right != NULL) {
        //Return 1 because treeNode has two children nodes
        return 1;
    }
    else {
        //Return 0 because treeNode does not have two children nodes
        return 0;
    }
}

int hasOneChild(TreeNode* treeNode) {
    if (treeNode->left != NULL && treeNode->right == NULL) {
        //Return 1 because treeNode has a left child but no right child
        return 1;
    }
    else if (treeNode->right != NULL && treeNode->left == NULL) {
        //Return 1 because treeNode has a right child but no left child
        return 1;
    }
    else {
        //Return 0 because treeNode either has no children or two children
        return 0;
    }
}

TreeNode* findMin(TreeNode* treeNode) {
    //BST will always have lower numbers on left - Traverse the entire left side to find the minimum treeNode
    while (treeNode->left != NULL) {
        treeNode = treeNode->left;
    }
    return treeNode;
}

int getHeight(TreeNode* treeNode) {
    //Base case: treeNode doesn't exist
    if (treeNode == NULL) {
        return 0;
    }
    else {
        int left = getHeight(treeNode->left);
        int right = getHeight(treeNode->right);

        if (left > right) {
            return (left + 1);
        }
        else {
            return (right + 1);
        }
    }
}

//int findMaxSide(int leftSide, int rightSide) {

//}
