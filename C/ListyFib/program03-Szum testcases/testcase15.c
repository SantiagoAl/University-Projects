// Sean Szumlanski
// COP 3502, Summer 2018

// ======================
// ListyFib: testcase15.c
// ======================


#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
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
	ListyInt *listy;
	int i, n[] = { 6387, 2887, 7276 };

	for (i = 0; i < 3; i++)
	{
		printf("F(%d) = ", n[i]);
		listyPrint(listy = fib(n[i]));
		destroyListyInt(listy);
	}

	return 0;
}
