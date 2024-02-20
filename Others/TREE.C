/**
* C PROGRAM TO IMPLEMENT A BINARY TREE
**/

#include <stdio.h>
#include <stdlib.h>

#define getnode() ((ptr) malloc (sizeof (struct Node)))

// STRUCTURE OF A NODE

typedef struct Node
	{
	int info;
	struct Node *LL,
	            *RL;
	}
	*ptr;

// NUMBER OF NODES

int CNT;

// CONSTRUCTION OF THE TREE

ptr make_tree ()
	{
	int data;

	while (printf ("\n\tEnter Data : "),
	       fflush (stdin), !scanf ("%d", &data))
	       puts ("\t[INVALID INPUT]");

	if (data && ++CNT)
		{
		ptr q = getnode();
		q -> info = data;

		printf ("\n\tLeft Child of [ %d ] :", q -> info);
		q -> LL = make_tree ();

		printf ("\n\tRight Child of [ %d ] :", q -> info);
		q -> RL = make_tree ();

		return (q);
		}

	return (NULL);
	}

// RECURSIVE PRE-ORDER TRAVERSAL

void pre_ord_R (ptr t)
	{
	if (!t) return;

	printf    (" %5d ", t -> info);
	pre_ord_R (t -> LL);
	pre_ord_R (t -> RL);
	}

// RECURSIVE IN-ORDER TRAVERSAL

void in_ord_R (ptr t)
	{
	if (!t) return;

	in_ord_R (t -> LL);
	printf   (" %5d ", t -> info);
	in_ord_R (t -> RL);
	}

// STACK IMPLEMENTATION

#define push(X) (Stack [TOP++] = X)
#define pop()   (Stack [--TOP])

int  TOP;
ptr* Stack;

// NON-RECURSIVE PRE-ORDER TRAVERSAL

void pre_ord_NR (ptr p)
	{
	while (p && (printf (" %5d ", p -> info),
	             p = push (p) -> LL) ||
	       TOP && (p = pop () -> RL, 1));
	}

// NON-RECURSIVE IN-ORDER TRAVERSAL

void in_ord_NR (ptr p)
	{
	while (p && (p = push (p) -> LL) ||
	       TOP && (printf (" %5d ", (p = pop ()) -> info),
	               p = p -> RL, 1));
	}

// MAIN FUNCTION

int main (void)
	{
	// TREE CONSTRUCTION

	ptr t = make_tree ();

	// RECURSIVE PRE-ORDER TRAVERSAL

	printf ("\n\tPreorder Traversal (Recursive) :\n\t");
	pre_ord_R (t);

	// RECURSIVE IN-ORDER TRAVERSAL

	printf ("\n\tInorder Traversal  (Recursive) :\n\t");
	in_ord_R (t);

	// MEMORY ALLOCATION FOR STACK

	Stack = (ptr*) malloc (CNT * sizeof (ptr));

	// NON-RECURSIVE PRE-ORDER TRAVERSAL

	printf ("\n\n\tPreorder Traversal (Non-Recursive) :\n\t");
	pre_ord_NR (t);

	// NON-RECURSIVE PRE-ORDER TRAVERSAL

	printf ("\n\tInorder Traversal  (Non-Recursive) :\n\t");
	in_ord_NR (t);

	return 0;
	}