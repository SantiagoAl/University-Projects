// Sean Szumlanski
// COP 3502, Summer 2018

// ======================
// ListyFib: testcase04.c
// ======================
// Tests the stringToListyInt() function.
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

	listyPrint(p = stringToListyInt("12345"));
	destroyListyInt(p);

	listyPrint(p = stringToListyInt("354913546879519843519843548943513179"));
	destroyListyInt(p);

	listyPrint(p = stringToListyInt(NULL));
	destroyListyInt(p);

	return 0;
}
