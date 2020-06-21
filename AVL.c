// AVL.C
//
// Code for ELEC278 Lab 4.  Some code has already been implemented.
// You will develop your own code - look for the comments.
//
// HISTORY:
//	14xxxx	XXX	First release
//	161004	HF	Some modifications for clarity, bug fixes
//	161025	DFA	Additional comments; code updates
//	171016	DFA	Code clean up

#include "avl.h"


Node *initNode (Key k, void *v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created, or NULL if no memory.
{
	Node *n = malloc(sizeof(Node));
	if (n != NULL)	{
		n->key = k;
		n->value = v;
		n->leftChild = NULL;
		n->rightChild = NULL;
		n->height = -1;
		}
	return n;
}//initNode()


Tree *initTree(void)
// Set up new tree. Allocates memory for Tree structure,
// then initializes root pointer to NULL.
{
	Tree* t = malloc(sizeof(Tree));
	if (t != NULL)
		t->root = NULL;
	return t;
}//initTree()


void printTree(Node* root)
// Print representation of tree. We make an assumption, because tree nodes
// actually have pointer to data, not actual data.  So assume that it is a
// pointer to an integer.
{
	printf("{");		// Tree starts with an opening curly bracket
	// then value of parent node
	printf("(%ld,%d)", (long) root->key, *(int*) root->value);
						// need to cast void pointer actual data type
	printf(",");		// children come next

	// left child. If NULL it will just print two empty braces,
	// otherwise it prints whole left tree.
	if (root->leftChild) {
		printTree(root->leftChild);
	} else
		printf("{}");
	// separate left child from right child
	printf(",");
	// right child. If NULL it will just print two empty braces,
	// otherwise it prints whole right tree.
	if (root->rightChild) {
		printTree(root->rightChild);
	} else
		printf("{}");
	printf("}");	// Tree ends with closing curly bracket
}//printTree()


int maxint(int a, int b)	{ return (a>=b) ? a : b; }


Node *find (Key k, Node *root)
// Find node in tree with key equal to k.  Returns NULL if no node found;
// otherwise returns pointer to node with key value.
{
	// termination condition #1
	if (root == NULL)	return NULL;	// No tree, no node with matching key
	// termination condition #2
	if (root->key == k)	return root;	// found node at root
	// Have to search subtree - figure out which one
	if (k > root->key)
		return find(k, root->rightChild);
	else
		return find(k, root->leftChild);
#if 0
	// slightly obscure way of doing if-then-else above
	return find (k, (k > root->key) ? root->rightChild : root->leftChild);
#endif
}// find()


void insert(Key k, void *v, Tree *t)
// Add new data item to tree.  Use two data components - key and actual data -
// to create new node and insert node in appropriate place.
{
	printf("Inserting %d\n", k);
	// Check if tree empty - if so, insert first node
	if (t->root == NULL) {
		Node *n = initNode(k, v);
		n->height = 0;
		t->root = n;
	} else	{
		t->root = insertNode(k, v, t->root);
		}
	return;
}//insert()


Node* rotateRight(Node* root)
// Rotate to right.  Returns new root pointer.
{
	printf("Rotate Right\n");
//---Your code goes here
//---<SNIP>---
	if (root != NULL)	{
		Node* left = root->leftChild;
		Node* leftRight = left->rightChild;
		root->leftChild = leftRight;
		left->rightChild = root;

		root->height = calcHeight(root);
		left->height = calcHeight(left);
		return left;
		}
//---<SNIP>---
	return root;
}//rotateRight()


Node* rotateLeft(Node* root)
// Rotate to left.  Returns new root pointer.
{
	printf("Rotate Left\n");
//---Your code goes here
//---<SNIP>---
	if (root != NULL)	{
		Node* right = root->rightChild;
		Node* rightLeft = right->leftChild;
		root->rightChild = rightLeft;
		right->leftChild = root;

		root->height = calcHeight(root);
		right->height = calcHeight(right);
		return right;
		}
//---<SNIP>---
	return root;
}//rotateLeft()


int getBalanceFactor(Node* root)
// Get balance factor - difference between left height and right height
{
	int	hr = -1, hl = -1;		// Default values
//---Your code goes here
//---<SNIP>---
	hr = (root->rightChild) ? root->rightChild->height : -1;
	hl = (root->leftChild) ? root->leftChild->height : -1;
//---<SNIP>---
	return hl - hr;
}//getBalanceFactor()


int calcHeight(Node* root)
// Calculate height of this node by adding 1 to maximum of left, right
// child height.
{
	int hrl = -1, hll = -1;		// Default values
//---Your code goes here
//---<SNIP>---
	if (root->rightChild != NULL)	hrl = root->rightChild->height;
	if (root->leftChild  != NULL)	hll = root->leftChild->height;
//---<SNIP>---
	return maxint(hrl, hll) + 1;
}//calcHeight();


Node* rebalance(Node* root)
// Check balance factor to see if balancing required (bf > 1 or bf < -1).
// If balancing required, perform necessary rotations.
{
	int bf = getBalanceFactor(root);
//---Your code goes here
//---<SNIP>---
	if (bf > 1) { // left
		int left_bf = getBalanceFactor(root->leftChild);
		if (left_bf >= 0) { //left
			printf("Node %d is unbalanced. Left of Left: ", root->key);
			return rotateRight(root);
		} else if (left_bf < 0) { // right
			printf("Node %d is unbalanced. Right of Left: ", root->key);
			root->leftChild = rotateLeft(root->leftChild);
			return rotateRight(root);
		}
	} else if (bf < -1) { //right
		int right_bf = getBalanceFactor(root->rightChild);
		if (right_bf >= 0) { //left
			printf("Node %d is unbalanced. Left of Right: ", root->key);
			root->rightChild = rotateRight(root->rightChild);
			return rotateLeft(root);
		} else if (right_bf < 0) { // right
			printf("Node %d is unbalanced. Right of Right: ", root->key);
			return rotateLeft(root);
		}
	}
//---<SNIP>---
	return root;
}//rebalance()


Node* insertNode(Key k, void *v, Node *root)
// Build new node and insert into (non-empty) tree. Check if insertion has
// created imbalance and rebalance if necessary.
{
	if (root==NULL) {
		Node *n = initNode(k, v);
		n->height = 0;
		return n;
	}
	if (k < root->key) {
		root->leftChild = insertNode(k, v, root->leftChild);
		root->height = calcHeight(root);
	}

	else if (k > root->key) {
		root->rightChild = insertNode(k, v, root->rightChild);
		root->height = calcHeight(root);
	}
	// Note - ignored equal case.
	return rebalance(root);
}//insertNode()


void inOrderT(Node* root) {
	if (root) {
		inOrderT(root->leftChild);
		printf("%d(h=%d,bf=%d) - ", root->key, root->height,getBalanceFactor(root));
		inOrderT(root->rightChild);
	}
}
