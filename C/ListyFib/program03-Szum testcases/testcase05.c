// Sean Szumlanski
// COP 3502, Summer 2018

// ======================
// ListyFib: testcase05.c
// ======================
// Tests the uintToListyInt() function.
//
// This is an excerpt of the testcase02.c file released with the assignment, which has been split
// into two test cases for grading.


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
	printf("\n");
}

int main(void)
{
	ListyInt *p;

	listyPrint(p = uintToListyInt(246810));
	destroyListyInt(p);

	listyPrint(p = uintToListyInt(0));
	destroyListyInt(p);

	listyPrint(p = uintToListyInt(INT_MAX));
	destroyListyInt(p);

	listyPrint(p = uintToListyInt(UINT_MAX));
	destroyListyInt(p);

	return 0;
}
