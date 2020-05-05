#include <stdio.h>
#include <stdlib.h>

//Defining a new ty 'Node' - value and pointer to next element
typedef struct Node {
	int			value;
	struct Node	*next;
} Node;


// LinkedList structure has pointer to first element, and count of elements in list.
typedef struct LinkedList {
	Node	*head;
	int		size;
} LinkedList;


// Check if LinkedList is empty. It is empty if head pointer is NULL
int isEmpty(LinkedList *l)
{
	return (l->head == NULL);
}


// Initialize LinkedList structure
void init(LinkedList *l)
{
    l->head = NULL;
    l->size = 0;
}


//***ADD*** 

// CREATE NEW NODE AND INITIALIZE VALUE AND POINTER
Node *createNode (int x, Node *nxt) 
{
	Node *pNode = (Node *)malloc (sizeof(Node));
	if (pNode != NULL)	{
		pNode->value = x;
		pNode->next = nxt;
		}
	return pNode;
}

// ADD TO EMPTY 
new = (node*)malloc(sizeof(Node));
new->next = NULL;
new->value = x;
if(Head==NULL) Head = new; 

// ADD TO FONT
// Create and initialize new Node structure with value 
// and current head_of_list pointer
// Make head-of-list point to new node
void addFront(LinkedList* l,int x)
{
    Node* newNode = createNode (x, l->head);
	printf ("Adding %d to front of list\n", x); 
    l->head = newNode;
    l->size++;
}

// ADD TO MIDDLE

// ADD TO END
void addEnd(LinkedList* l,int x)
{
    Node* newNode = createNode (x, NULL);
	printf ("Adding %d to end of list\n", x);
	// start by increasing size of linked list
    l->size++;
	// find current last Node, so it can be made to point to the new node
	if (isEmpty (l))	{
		// LinkedList currently empty - new node becomes first in list
		l->head = newNode;
	} else	{
		// Not empty - have to find last Node in current list and make
		// it point to new node.
		Node* ptr = l->head;
		// Traverse list until node found that doesn't point to a next one
		while(ptr->next!=NULL)	{
			ptr = ptr->next;
			}
		// ptr points to a Node with no next Node; make this Node point to
		// new one
		ptr->next = newNode;
		}
}


//***DELETE***

// DELETE FRONT
void removeFront(LinkedList* l)
{
	printf ("Remove item at front of list\n");
	if (!isEmpty (l))	{
		// List is not empty, so there is a first Node to delete.
		Node *ptr = l->head;		// point to first node
		// Note that list will be one shorter
		l->size--;
		// head of list is now element after first
		l->head = l->head->next;
		// discard node we no longer need
		free(ptr);
		}
}


// DELETE END
void removeEnd(LinkedList* l)
{
	printf ("Remove item at end of list\n");
	// First determine if any work to do
	if (!isEmpty (l))	{
		// Special case - if there is only one Node
		if (l->size==1)	{
			removeFront(l);
		} else	{
			// More than 1. Note how this code requires that a Node
			// be found that points to a last Node (one with a NULL
			// next pointer, and that doesn't work for the list with
			// only 1 Node.  Fun exercise for the student - think about 
			// how to redesign data and code so that all cases can
			// be handled with one piece of code.
			Node* ptr = l->head;
			Node* delPtr;

			// As long as the Node we're pointing to isn't the end of
			// the list, move to next Node
			while(ptr->next->next)	{
				ptr = ptr->next;
				}
			delPtr = ptr->next;
			ptr->next = NULL;
			free(delPtr);
			l->size--;
			}
		}
}

//DELETE ENTIRE LIST - by repeatedly deleting first Node
void destroy(LinkedList* l)
{
	while(!isEmpty(l))	{
		removeFront(l);
		}
}

// DELETE VALUE - Remove first Node in list whose value is x
void removeValue(LinkedList* l,int x)
{
	printf ("Find first %d in list and remove it\n", x);
	if (isEmpty(l))	return;
	// If first Node has value, remove first node
	if (l->head->value == x)
		removeFront (l);
	else	{
		// Wasn't in first position - traverse until we find one.  We have
		// to keep track of both the node that holds the value and the one
		// prior to it, so we can easily delete the node containing the value.
		Node *prev = l->head;			// points to first Node
		Node *curr = prev->next;		// points to second
		// As long as we have a current node, check it for value
		while (curr != NULL)	{
			if (curr->value == x)	{
				// current node has value we're looking for
				// Previous node needs to point to the one after the current
				// node (to remove th ecurrent node from the list) then the
				// current node needs to be freed.
				prev->next = curr->next;
				l->size--;
				free (curr);
				// basically, that's it
				break;
				}
			// Not found yet - advance both pointers
			prev = curr;
			curr = curr->next;
			}
		}
}

//FIND SMALLEST VALUE IN LINKEDLIST AND SUBTRACT THAT VALUE FROM EACH VALUE
void update(LinkedList* l)
{
	printf ("Subtract smallest value from all values in list\n");
	if (!isEmpty(l))	{
		Node	*ptr = l->head;
		int		min = l->head->value;	// it is a starting point
		// Alternately,
		// int	min = MAXINT;			// smallest value must be smaller!
		// Traverse list, looking for smaller values than what we have so far
		while (ptr != NULL)	{
			if (ptr->value < min)
				// found one even smaller
				min = ptr->value;
			ptr = ptr->next;
			}
		// At this point, we have checked all list elements and found smallest
		// value.  Subtract value found from each list element.
		for (ptr = l->head; ptr != NULL; ptr = ptr->next)	{
			ptr->value -= min;
			}
		}
}