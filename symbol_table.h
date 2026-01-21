#include "lexer.h"

// typedef struct Node {
//    int height;
//    char *name;
//    char *type;
//    struct Node *left, *right;
// } Node;

typedef struct Node {
   Token key;
   int height;
   struct Node *left, *right;
} Node;

/* function: inserts a new node to the tree
   input: proot: pointer to the pointer to the tree root
          x: the key of the new node
   output: returns a pointer to the newly inserted node
           returns NULL if insertion is not successful
*/
Node *insertNode(Node **proot, Token x);

/* function: searches for a node in the tree
   input: root: pointer to the tree root
          x: the key of of the node to be searched
   output: returns a pointer to the found node
           returns NULL if no such node exists
*/
Node *findNode(Node *root, Token x);

/* function: removes a node from the tree without freeing it
   input: proot: pointer to the pointer to the tree root
          x: the key of of the node to be deleted
   output: returns a pointer to the deleted node
           returns NULL if no such node exists
*/
Node *deleteNode(Node **proot, Token x);

/* function: deletes all the nodes in the tree and frees the memory
             occupied by them
   input: root: pointer to the tree node
   output: none
*/
void destroyTree(Node *root);

void printTable(Node *root);
