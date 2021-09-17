// Sean Szumlanski
// COP 3502, Summer 2018

// ======================
// ListyFib: testcase12.c
// ======================


#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "ListyFib.h"

#define NUM_POINTERS 9

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
	ListyInt *ptrs[NUM_POINTERS];
	int i = 0;
	unsigned int *u;

	ptrs[i++] = uintToListyInt(0);
	ptrs[i++] = uintToListyInt(1);
	ptrs[i++] = uintToListyInt(1000000);
	ptrs[i++] = uintToListyInt(2000000);
	ptrs[i++] = uintToListyInt(2147483646);
	ptrs[i++] = uintToListyInt(2147483647);
	ptrs[i++] = uintToListyInt(2147483648);
	ptrs[i++] = uintToListyInt(4294967294);
	ptrs[i++] = uintToListyInt(4294967295);

	i = 0;

	printf("ptrs[%d] = uintToListyInt(\"%u\"): ", i, 0);
	listyPrint(ptrs[i++]);

	printf("ptrs[%d] = uintToListyInt(\"%u\"): ", i, 1);
	listyPrint(ptrs[i++]);

	printf("ptrs[%d] = uintToListyInt(\"%u\"): ", i, 1000000);
	listyPrint(ptrs[i++]);

	printf("ptrs[%d] = uintToListyInt(\"%u\"): ", i, 2000000);
	listyPrint(ptrs[i++]);

	printf("ptrs[%d] = uintToListyInt(\"%u\"): ", i, 2147483646);
	listyPrint(ptrs[i++]);

	printf("ptrs[%d] = uintToListyInt(\"%u\"): ", i, 2147483647);
	listyPrint(ptrs[i++]);

	printf("ptrs[%d] = uintToListyInt(\"%u\"): ", i, (unsigned int)2147483648);
	listyPrint(ptrs[i++]);

	printf("ptrs[%d] = uintToListyInt(\"%u\"): ", i, (unsigned int)4294967294);
	listyPrint(ptrs[i++]);

	printf("ptrs[%d] = uintToListyInt(\"%u\"): ", i, (unsigned int)4294967295);
	listyPrint(ptrs[i++]);

	printf("\n");

	for (i = 0; i < NUM_POINTERS; i++)
	{
		// None of these should be NULL, so it should be safe to dereference u.
		u = listyIntToUint(ptrs[i]);
		printf("listyIntToUint( ptrs[%d] ): %u\n", i, *u);
		free(u);
	}

	for (i = 0; i < NUM_POINTERS; i++)
		destroyListyInt(ptrs[i]);

	return 0;
}
