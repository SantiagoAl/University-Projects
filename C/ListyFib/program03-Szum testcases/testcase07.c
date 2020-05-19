// Sean Szumlanski
// COP 3502, Summer 2018

// ======================
// ListyFib: testcase07.c
// ======================
// Similar to the previous test case. Tests for a variety of functions: stringToListyInt(),
// listyIntToString(), and destroyListyInt().
//
// This is identical to the testcase04.c file released with the assignment, except for a minor
// modification to the listyPrintHelper() function.


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
	char *str;
	ListyInt *p;

	listyPrint(p = stringToListyInt("12345"));
	printf("%s\n", str = listyIntToString(p));
	free(str);
	destroyListyInt(p);

	listyPrint(p = stringToListyInt("354913546879519843519843548943513179"));
	printf("%s\n", str = listyIntToString(p));
	free(str);
	destroyListyInt(p);

	listyPrint(p = stringToListyInt(NULL));
	str = listyIntToString(p);
	assert(str == NULL);
	destroyListyInt(p);

	listyPrint(p = uintToListyInt(246810));
	printf("%s\n", str = listyIntToString(p));
	free(str);
	destroyListyInt(p);

	listyPrint(p = uintToListyInt(0));
	printf("%s\n", str = listyIntToString(p));
	free(str);
	destroyListyInt(p);

	listyPrint(p = uintToListyInt(INT_MAX));
	printf("%s\n", str = listyIntToString(p));
	free(str);
	destroyListyInt(p);

	listyPrint(p = uintToListyInt(UINT_MAX));
	printf("%s\n", str = listyIntToString(p));
	free(str);
	destroyListyInt(p);

	return 0;
}
