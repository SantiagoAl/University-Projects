// Sean Szumlanski
// COP 3502, Summer 2018

// ======================
// ListyFib: testcase09.c
// ======================
// Essential test of the fib() function.
//
// This is identical to the testcase06.c file released with the assignment, except for a minor
// modification to the listyPrintHelper() function.


#include <assert.h>
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
	printf("\n");
}

int main(void)
{
	int i;
	ListyInt *p;

	for (i = 0; i <= 50; i++)
	{
		printf("F(%d) = ", i);
		listyPrint(p = fib(i));
		destroyListyInt(p);
	}

	return 0;
}
