// Sean Szumlanski
// COP 3502, Summer 2018

// ===============================
// ListyFib: valgrind-testcase03.c
// ===============================
// This is a copy of testcase08.c from the grading test cases.


#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "ListyFib.h"

// Recursive helper function for printing the digits in a linked list in reverse order.
void listyPrintHelper(Node *current)
{
	if (current == NULL)
		return;

	listyPrintHelper(current->next);

	// Each node should hold a single digit.
	assert(current->digit >= 0 && current->digit <= 9);
	printf("%d", current->digit);
}

// Print a ListyInt (followed by a newline character).
void listyPrint(ListyInt *p)
{
	if (p == NULL || p->head == NULL)
	{
		printf("(null pointer)\n");
		return;
	}

	listyPrintHelper(p->head);
}

int main(void)
{
	int i;
	ListyInt *p, *q, *r;

	// Calculate INT_MAX + 1.
	p = uintToListyInt(INT_MAX);
	q = uintToListyInt(1);
	r = listyAdd(p, q);

	// Demonstrate overflow.
	printf("Overflow style:\n%d + %d = %d\n\n", INT_MAX, 1, INT_MAX + 1);

	// Print result of INT_MAX + 1 with ListyInts.
	printf("ListyInt style:\n");
	listyPrint(p);
	printf(" + ");
	listyPrint(q);
	printf(" = ");
	listyPrint(r);
	printf("\n\n");

	// Free memory.
	destroyListyInt(p);
	destroyListyInt(q);
	destroyListyInt(r);


	// Now calculate UINT_MAX + 1.
	p = uintToListyInt(UINT_MAX);
	q = uintToListyInt(1);
	r = listyAdd(p, q);

	// Demonstrate overflow.
	printf("Overflow style:\n%u + %u = %u\n\n", UINT_MAX, 1, UINT_MAX + 1);

	// Print result of UINT_MAX + 1 with ListyInts.
	printf("ListyInt style:\n");
	listyPrint(p);
	printf(" + ");
	listyPrint(q);
	printf(" = ");
	listyPrint(r);
	printf("\n");

	// Free memory.
	destroyListyInt(p);
	destroyListyInt(q);
	destroyListyInt(r);


	return 0;
}
