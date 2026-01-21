#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

#define max(i, j) (((i) > (j)) ? (i) : (j))

int getHeight(Node *root) {
	if (root == NULL) {
		return 0;
	}
	return -1;
}

void updateHeight(Node *root) {
	int hleft = root->left ? root->left->height : -1;
	int hright = root->right ? root->right->height : -1;
	root->height = max(hleft, hright) + 1;
}

Node *createNode(Token x) {
	Node *newNode = malloc(sizeof(Node));
	newNode->key = x;
	newNode->height = 0;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void rightRotate(Node **proot) {
	Node *root = *proot;
	Node *left = root->left;
	root->left = left->right;
	left->right = root;
	*proot = left;
	updateHeight(root);
	updateHeight(left);
}

void leftRotate(Node **proot) {
	Node *root = *proot;
	Node *right = root->right;
	root->right = right->left;
	right->left = root;
	*proot = right;
	updateHeight(root);
	updateHeight(right);
}

void rebalance(Node **proot) {
	Node *root = *proot;
	int hleft = getHeight(root->left);
	int hright = getHeight(root->right);
	if (abs(hleft - hright) <= 1) {
		return;
	}
	Node *heavyChild;
	if (hleft > hright) { // left
		heavyChild = root->left;
		if (getHeight(heavyChild->left) > getHeight(heavyChild->right)) { // case1
			rightRotate(&root);
		}
		else { // case2
			leftRotate(&(root)->left);
			rightRotate(&root);
		}
	}
	else { // right
		heavyChild = root->right;
		if (getHeight(heavyChild->left) > getHeight(heavyChild->right)) { // case3
			rightRotate(&(root)->right);
			leftRotate(&root);
		}
		else { // case4
			leftRotate(&root);
		}
	}
}

Node *insertNode(Node **proot, Token x) {
	// Token *token = *ptoken;
	if (*proot == NULL) {
		return *proot = createNode(x);
	}
	// if (x.value == NULL) {//when the tree is not build
	//  return *proot = createNode(x);
	// }
	if (strcmp((*proot)->key.value, x.value) == 0) {//have same value
		return NULL;
	}
	Node *newNode;
	if (strcmp((*proot)->key.value, x.value) == 0) {//find the right position to put the value
		newNode = insertNode(&(*proot)->left, x);//same type put left
	}
	else {
		newNode = insertNode(&(*proot)->right, x);//otherwise,put right
	}
	updateHeight(*proot);
	rebalance(&(*proot));
	return newNode;
}

Node *findNode(Node *root, Token x) {
	if (root == NULL) {
		return NULL;
	}
	if (strcmp((root)->key.value, x.value) == 0) {
		return root;
	}
	if (strcmp((root)->key.value, x.value) == 0) {
		return findNode(root->left, x);
	}
	else {
		return findNode(root->right, x);
	}
}

Node *deleteMin(Node **proot) {
	// remove an delete the minimum node
	// in the sub-tree lead by node
	Node *root = *proot;
	Node *minNode;
	if (root->left == NULL) {
		// root is the minimum node
		// and it has no left child
		minNode = root;
		root = root->right;
		return minNode;
	}
	minNode = deleteMin(&(root)->left);
	updateHeight(root);
	rebalance(&root);
	return minNode;
}

Node *deleteRoot(Node **proot) {
	// remove and return the root
	Node *root = *proot;
	Node *currNode = root;
	if (root->left == NULL) {
		root = root->right;
		return currNode;
	}
	if (root->right == NULL) {
		root = root->left;
		return currNode;
	}
	// root has two children
	Node *minNode;
	minNode = deleteMin(&(root)->right);
	minNode->left = root->left;
	minNode->right = root->right;
	root = minNode;
	return currNode;
}

// Node *deleteNode(Node **proot, Token x) {
// 	Node *root = *proot;
// 	Node *matchNode;
// 	if (root == NULL) {
// 		return NULL;
// 	}
// 	if (strcmp((root)->key.type, x.type)) {
// 		matchNode = deleteNode(&(root)->left, x);
// 	}
// 	else if (root->key < x) {
// 		matchNode = deleteNode(&(root)->right, x);
// 	}
// 	else {
// 		matchNode = deleteRoot(&root);
// 	}
// 	if (root != NULL) {
// 		updateHeight(root);
// 		rebalance(&root);
// 	}
// 	return matchNode;
// }

void destroyTree(Node *root) {
	if (root == NULL) {
		return;
	}
	destroyTree(root->left);
	destroyTree(root->right);
	free(root);
}

void printTable(Node *root) {
	if (root == NULL) {
		return;
	}
	if (root->left != NULL || root->right != NULL) {
		printTable(root->left);
		printTable(root->right);
	}
	// printf("------------------------------------------------------------------\n");
	printf("Name: %-5s, type: NULL\n", root->key.value);
}


