// Sean Szumlanski
// COP 3502, Summer 2018

// ===============================
// ListyFib: valgrind-testcase02.c
// ===============================
// This is a copy of testcase16.c from the grading test cases.


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

// Make the ListyInt for 1.
ListyInt *szOne(void)
{
	ListyInt *listy = malloc(sizeof(ListyInt));

	if (listy == NULL)
		return NULL;

	listy->head = malloc(sizeof(Node));
	listy->length = 1;

	if (listy->head == NULL)
	{
		free(listy);
		return NULL;
	}

	listy->head->digit = 1;
	listy->head->next = NULL;

	return listy;
}

int main(void)
{
	int i;
	ListyInt *listy;

	listy = szOne();
	listyPrint(listy);
	for (i = 0; i < 100; i++)
	{
		plusPlus(listy);
		listyPrint(listy);
	}
	destroyListyInt(listy);

	listy = uintToListyInt(UINT_MAX);
	listyPrint(listy);
	for (i = 0; i < 100; i++)
	{
		plusPlus(listy);
		listyPrint(listy);
	}
	destroyListyInt(listy);

	return 0;
}
