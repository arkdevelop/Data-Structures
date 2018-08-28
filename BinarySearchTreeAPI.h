#ifndef BINSEARCHTREE_BINARYSEARCHTREEAPI_H
#define BINSEARCHTREE_BINARYSEARCHTREEAPI_H

/**
 * Function pointer typedefs
 */
typedef int (*CompareFunc)(const void* a, const void* b);
typedef void (*DeleteFunc)(void* data);
typedef void (*PrintFunc)(void* data);

/**
 * Typedef the void* to make the API cleaner and more readable
 */
typedef void* TreeDataPtr;

/**
 * A single binary tree node with left and right branches
 * void *data
 */
typedef struct binTreeNode {
    TreeDataPtr data;
    struct binTreeNode* left;
    struct binTreeNode* right;
    struct binTreeNode* parent; //Optional but useful
    //Tree* parentTree; //Optional but gets you access to function pointers
} TreeNode;

/**
 * Definition of the binary tree
 */
typedef struct binTree {
    TreeNode* root;
    CompareFunc compareFunc;
    DeleteFunc deleteFunc;
    PrintFunc printFunc;
    int count;
    //Additions must work with abstract data types
    //Additional function pointers to generalize tree
} Tree;

/**
 * Creates a TreeNode. TreeNode children are set to NULL and data is set
 * to the passed in data
 * @param data The data to be stored within the Node
 * @return Newly created TreeNode
 */
TreeNode* createTreeNode(TreeDataPtr data);

/**
 * Allocates memory for a tree and assigned function pointers
 * @param compare Function pointer to compare data in tree Nodes
 * @param del Function pointer to delete data from tree Nodes
 * @param print Function pointer to print data from tree Nodes
 * @return Newly created tree
 */
Tree* createBinTree(CompareFunc compare, DeleteFunc del, PrintFunc print);

/**
 * Remove all items and free memory
 * @param Tree toDestroy
 * @return void
 */
void destroyBinTree(Tree* toDestroy);

/**
 * Recursive call for destroyBinTree to delete every treeNode of a tree
 * @param TreeNode tempNode
 * @param DeleteFunc del
 * @return void
 */
void destroyBinTreeSub(TreeNode* tempNode, DeleteFunc del);

/**
 * Add data to a tree
 * @param Tree theTree
 * @param TreeDataPtr data
 * @return void
 */
void addToTree(Tree* theTree, TreeDataPtr data);

/**
 * Recursively find where to insert the new Node
 * @param TreeNode treeNode
 * @param TreeDataPtr data
 * @param CompareFunc compare
 * @return void
 */
TreeNode* insert(TreeNode* treeNode, TreeDataPtr data, CompareFunc compare);

/**
 * Remove data from the tree
 * @param Tree theTree
 * @param TreeDataPtr data
 * @return void
 */
void removeFromTree(Tree* theTree, TreeDataPtr data);

/**
 * Recursive delete function for tree
 * @param TreeNode tempNode
 * @param TreeDataPtr data
 * @param CompareFunc compare
 * @return TreeNode
 */
TreeNode* removeFromTreeSub(TreeNode* tempNode, TreeDataPtr data, CompareFunc compare, DeleteFunc del);

/**
 * Searches the tree for the target data
 * @param Tree theTree
 * @param TreeDataPtr data
 * @return NULL if fail, otherwise return data
 */
TreeDataPtr findInTree(Tree* theTree, TreeDataPtr data);

/**
 * Recursively finds the treeNode in the tree
 * @param TreeNode treeNode
 * @param TreeDataPtr data
 * @param CompareFunc compare
 * @return void
 */
TreeNode* findInTreeSub(TreeNode* treeNode, TreeDataPtr data, CompareFunc compare);

/**
 * Get data from the root of the tree if it exists
 * @param Tree theTree
 * @return NULL if tree is empty, otherwise return root
 */
TreeDataPtr getRootData(Tree* theTree);

/**
 * Prints the tree using an inOrder traversal
 * @param Tree theTree
 * @param PrintFunc printData
 * @return void
 */
void printInOrder(Tree* theTree, PrintFunc printData);

/**
 * Recursively prints treeNodes in order
 * @param Tree theTree
 * @param TreeNode treeNode
 * @param PrintFunc printData
 * @return void
 */
void printInOrderSub(Tree* theTree, TreeNode* treeNode, PrintFunc printData);

/**
 * Prints the tree using a preOrder traversal
 * @param Tree theTree
 * @param PrintFunc printData
 * @return void
 */
void printPreOrder(Tree* theTree, PrintFunc printData);

/**
 * Recursively prints treeNodes in pre order
 * @param Tree theTree
 * @param TreeNode treeNode
 * @param PrintFunc printData
 * @return void
 */
void printPreOrderSub(Tree* theTree, TreeNode* treeNode, PrintFunc printData);

/**
 * Prints the tree using a postOrder traversal
 * @param Tree theTree
 * @param PrintFunc printData
 * @return void
 */
void printPostOrder(Tree* theTree, PrintFunc printData);

/**
 * Recursively prints treeNodes in post order
 * @param Tree theTree
 * @param TreeNode treeNode
 * @param PrintFunc printData
 * @return void
 */
void printPostOrderSub(Tree* theTree, TreeNode* treeNode, PrintFunc printData);

/**
 * Checks if a tree is empty
 * @param Tree theTree
 * @return 0 if false, 1 otherwise
 */
int isTreeEmpty(Tree* theTree);

/**
 * Checks if a single Node is a leaf (No children)
 * @param TreeNode treeNode
 * @return 0 if false, 1 otherwise
 */
int isLeaf(TreeNode* treeNode);

/**
 * Checks if a single Node has two children
 * @param TreeNode treeNode
 * @return 0 if false, 1 otherwise
 */
int hasTwoChildren(TreeNode* treeNode);

/**
 * Checks if a single Node has one child
 * @param TreeNode treeNode
 * @return 0 if false, 1 otherwise
 */
int hasOneChild(TreeNode* treeNode);

/**
 * Finds the minimum value given a specific treeNode
 * @param TreeNode treeNode
 * @return TreeNode
 */
TreeNode* findMin(TreeNode* treeNode);

/**
 * Gets the height of a particular Node in the tree
 * @param TreeNode *treeNode
 * @return (1-Based) height for the tree
 */
int getHeight(TreeNode* treeNode);

/**
 * Gets the maximum left/right of a particular Node in the tree
 * @param TreeNode *treeNode
 * @return (1-Based) max side for the Node
 */
int findMaxSide(int leftSide, int rightSide);

#endif //BINSEARCHTREE_BINARYSEARCHTREEAPI_H
