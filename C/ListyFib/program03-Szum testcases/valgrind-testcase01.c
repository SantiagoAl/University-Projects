// Sean Szumlanski
// COP 3502, Summer 2018

// ===============================
// ListyFib: valgrind-testcase01.c
// ===============================
// This is a copy of testcase09.c from the grading test cases.


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
