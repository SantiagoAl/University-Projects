// Sean Szumlanski
// COP 3502, Summer 2018

// ======================
// ListyFib: testcase13.c
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

void uintHandler(unsigned int *u)
{
	if (u == NULL)
		printf("NULL\n");
	else
		printf("%u\n", *u);

	free(u);
}

int main(void)
{
	ListyInt *one, *max, *sum;
	unsigned int *u;

	one = szOne();
	max = uintToListyInt(UINT_MAX);
	sum = listyAdd(max, one);

	printf("via uintToListyInt()\n");
	printf("====================\n");
	printf("UINT_MAX + 1: "); listyPrint(sum);

	u = listyIntToUint(max);
	printf("listyIntToUint(UINT_MAX): ");
	uintHandler(u);

	u = listyIntToUint(sum);
	printf("listyIntToUint(UINT_MAX + 1): ");
	uintHandler(u);

	printf("\n\n");

	destroyListyInt(max);
	destroyListyInt(sum);

	// Now repeat the exercise using stringToListyInt().
	max = stringToListyInt("4294967295");
	sum = listyAdd(max, one);

	printf("via stringToListyInt()\n");
	printf("======================\n");
	printf("UINT_MAX + 1 = "); listyPrint(sum);

	u = listyIntToUint(max);
	printf("listyIntToUint(UINT_MAX): ");
	uintHandler(u);

	u = listyIntToUint(sum);
	printf("listyIntToUint(UINT_MAX + 1): ");
	uintHandler(u);

	printf("\n");

	destroyListyInt(max);
	destroyListyInt(sum);

	destroyListyInt(one);

	return 0;
}
