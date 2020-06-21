// BST.C [140916]
// 
// Code for ELEC278 Lab 3.  Some code has already been implemented.
// You will develop your own code - look for the comments.
// ---<SNIP>----
// Limitations:
// (a) This code seems designed not to handle empty trees - tree setup
// requires initial node and delete() doesn't have any way of clearing
// root node pointer in tree structure, when last node is deleted from tree.
// (b) This code copies contents from one node to another node when moving
// moving nodes, rather than changing pointers.  This is OK for small data,
// but not if data content of node is big.
// History:
//	14xxxx			Original
//	161013	DFA		Corrected initNode()
//	171002	DFA		Additional comments; reordered functions
//	171012	DFA		Modified height() to correct error
//	171012  DFA		Modified delete() to handle case of only 1 node
//	171012	DFA		findParentHelper() - segfault only 1 node fixed
//	171012	DFA		findParentHelper() - doesn't work if node doesn't exist
//	171012	DFA		Corrected syntax errors in solution
//
// ---<SNIP>----

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

//initialize node 
Node *initNode (Key k, void *v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created.
{
	Node *n = malloc(sizeof(Node));
	// initialize node if memory obtained
	if (n != NULL)	{
		n->key = k;
		n->value = v;
		n->leftChild = NULL;
		n->rightChild = NULL;
		}
	return n;
}//initNode()

//initialize tree
Tree *initTree(Key k, void *v)
// Set up new tree. Allocates memory for Tree structure, then
// calls initNode() to allocate first node.
{
	Tree* t = malloc(sizeof(Tree));
	if (t != NULL)
		t->root = initNode(k,v);
	return t;
}//initTree()


void printTreeExplanation (void)
// Prints hint to reader what to expect on screen
	{
		static int done = 0;
	if (!done)	{
		printf ("First time explanation of tree display:\n");
		printf ("Every node is displayed as a comma-separated pair within brackets:");
		printf (" (kk,vv)\n");
		printf ("A tree starts with a { and ends with a }.  An empty tree will be {}\n");
		printf ("A tree with no children will be { (kk,vv),{},{} }\n");
		printf ("If either subtree is populated, it will be shown using the same ");
		printf ("technique\n============\n\n");
		done = 1;
		}
}//printTreeExplanation()


void printTree (Node* root)
// Print whole tree. We cannot make it look pretty graphically, so we add some
// characters to make it a little easier to understand.  We also don't really
// know what the value field is - it is declared to be a void pointer - so we
// treat it as though it points to an integer.
{
	// assume printTree magically know the types in the tree node
	printTreeExplanation();
	// start of this tree
	printf("{");
	// values in the root node (assuming value is pointing to an integer)
	printf("(%ld,%d),", root->key, *(int*)root->value);
	
	// Now show left subtree or {} if there is no left subtree
	if (root->leftChild != NULL)	printTree(root->leftChild);
	else							printf("{}");
	// Marker between left and right subtrees		
	printf(",");
	// Now show right subtree or {} if there is no right subtree
	if (root->rightChild != NULL)	printTree(root->rightChild);
	else							printf("{}");
	// Close display of this tree with closing curly bracket	
	printf("}");
}//printTree()


Node *find (Key k, Node *root)
// Function locates node with key value equal to parameter k. Parameter
// root holds pointer to root node of tree. Function returns immediately
// if either root pointer is null, or the node that root points to has
// key value sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the left or right
// subtree.
{
	// termination conditions - either true, search is ended
	if ((root == NULL) || (root->key == k))	return root;
	// search continues.  Since this is a search tree, we know that
	// every key in the right subtree is bigger than the key in the tree's
	// root, and every key in the left subtree is smaller than the key in
	// the tree's root.  That allows us to choose the appropriate subtree
	// to search.
	if (k > root->key)
		// Key value sought is larger than current node key, so search right
		// subtree
		return find(k,root->rightChild);
	else
		// Key value sought is smaller than current node key (the equal case
		// was handled as a termination condition in the first line), so
		// search left subtree
		return find(k,root->leftChild);	
}//find()



int insert(Key k, void *v, Node *root)
// Function inserts a new node into the tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.
{
	int result = 0;
	// this if statement can only be true with the first root (root of whole tree)
	if (root == NULL)	{
		Node *n = initNode(k,v);
		root = n;
		return 1;
		}
	
	/* already exists in tree ==> can't insert */
	if (root->key == k)
		result = 0;
	else if (k < root->key) {
		// key value less than key value in root node - try to insert into left
		// subtree, if it exists.
		if (root->leftChild != NULL)
			// there is a left subtree - insert it
			result = insert(k, v, root->leftChild);
		else {
			// new Node becomes the left subtree
			Node *n = initNode(k,v);
			root->leftChild = n;
			result = 1;
			}
	} else if (k > root->key) {			// test actually redundant
		// key is greater than this nodes key value, so value goes into right
		// subtree, if it exists
		if (root->rightChild != NULL)
			// there is a right subtree - insert new node
			result = insert(k,v,root->rightChild);
		else {
			// no right subtree - new node becomes right subtree
			Node*n = initNode(k,v);
			root->rightChild = n;
			result = 1;
			}
		}
	return result;	
}//insert()

//
int intmax(int a, int b)
// YOU WILL USE THIS FUNCTION WHEN YOU IMPLEMENT HEIGHT() !!
// Useful function - returns the greater value of two integers.
// Called intmax, not max, because max already exists.
// It is a chance to see the conditional value in C - a value that is the
// first one (after the ?) if the condition is true, or the second one (after
// the :) if the condition is false.
{
	return (a>=b) ? a : b;
}//intmax()


int height(Node *root)
// Height definition:
// Height of an empty tree is -1.  Height of a leaf node is 0. Height of other
// nodes is 1 more than bigger height of node's two subtrees.
{ 
	// your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ---<SNIP>----
	int		nodeheight = -1;	// default returned for empty tree
	if (root != NULL)	{
		int leftheight = height (root->leftChild);
		int rightheight = height (root->rightChild);
		nodeheight = 1 + intmax (leftheight, rightheight);
		}
	return nodeheight;
	// ---<SNIP>----
}//height()


Node* findParentHelper (Key k, Node* root)
// Help find parent of node with key == k. Parameter root is node with
// at least one child (see findParent()).
{
	// your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ---<SNIP>----
	// if either child's key equals k, have found the parent
	// Check left first
	if (root->leftChild)	{
		// have left subtree. Is root of that tree the one with matching key?
		if (k == root->leftChild->key)	return root;
		// Should we search further down left subtree?
		else if (k < root->key)
			return findParentHelper(k, root->leftChild);
		}

	// Next, check right	
	if (root->rightChild)
		if (k == root->rightChild->key)	return root;
	
	// otherwise go down tree
	if (k < root->key)	return findParentHelper(k, root->leftChild);
	else				return findParentHelper(k, root->rightChild);

	// ---<SNIP>----
}//findparenthelper()


Node* findParent(Key k, Node *root)
// 
{
	// Deal with special special cases which could only happen for root
	// of whole tree
	if (root == NULL)	return root;	
	// real root doesn't have parent so we make it parent of itself
	if (root->key == k)	return root;	
	// root has no children
	if ((root->leftChild == NULL) && (root->rightChild == NULL)) 
			return NULL;
	
	// Deal with cases where root has at least one child
	return findParentHelper(k, root);
}//findParent()


void delete (Node *p, Node *n)
// Delete node pointed to by n.
// Parameters:
//	n	- points to node to be deleted
//	p	- points to parent of node to be deleted.
{
	// your code goes here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// ---<SNIP>----
	// Deletion has 3 cases - no subtrees, only left or right subtree, or both
	// left and right subtrees.
	Node *deleteNode = n;		// Save copy of pointer to node to delete.

	if (n->leftChild)
	{
		p = n;
		n = n->leftChild;
		/* get to rightmost child of the left subtree */
		while (n->rightChild) {
			p = n;
			n = n->rightChild;
			}
		
		/* overwrite deleteNode (key,value) with (key,value) of rightmost child of left subtree */
		deleteNode->key = n->key;
		deleteNode->value = n->value;
		delete(p,n);
	} else if (n->rightChild) {
		p = n;
		n = n->rightChild;
		/* get to leftmost child of the right subtree */
		while(n->leftChild)
		{
			p = n;
			n = n->leftChild;
		}
		/* overwrite deleteNode (key,value) with (key,value) of leftmost child of right subtree */
		deleteNode->key = n->key;
		deleteNode->value = n->value;
		delete(p,n);
	} else	{
		// termination condition: we have reached leaf node. Deleting leaf is
		// easy - just figure out which parent pointer points to node and
		// update that pointer. Need to be careful - if we are deleting only
		// node in tree, then there is no parent to update.
		if (p != NULL)	{
			// There is parent - are we deleting left or right subtree?
			if (p->leftChild == n)			p->leftChild = NULL;
			else if (p->rightChild == n)	p->rightChild = NULL;
			// We are ignoring possibility that neither subtree pointer
			// points to node.
			}
		// If there was no parent, then that means node to delete is only
		// node in tree. This code has no means of updating tree data structure
		// to account for this.  Given that creation of tree also creates first
		// node, suspect designer did not intend to allow for delete of last
		// node.
		free(n);
		}	
	// ---<SNIP>----
}//delete()


int withdraw(Key k, Node* root, Node* n)
// Withdraw does two things:
//	return a copy of the node with key k (and value v)
//	Delete the node with key k from the tree while ensuring the tree remains valid
{
	Node *p, *m;
	m = find(k, root);
	
	if (m != NULL)	{
		// create a copy of the node with the same key and value
		n = initNode(m->key,m->value);
		p = findParent(k,root);
		// can delete the node
		delete(p,m);
		return 1;
	}
	
	return 0;	
}//withdraw()
