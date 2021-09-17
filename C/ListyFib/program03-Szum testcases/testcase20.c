// Sean Szumlanski
// COP 3502, Summer 2018

// ======================
// ListyFib: testcase20.c
// ======================
// Generate a very large string and convert it to a ListyInt. This effectively tests whether the
// stringToListyInt() function is linear in runtime. This can be considered a bonus test case, since
// the PDF didn't require a linear runtime for stringToListyInt(). However, one should always be
// concerned about implementing efficient versions of the functions required for assignments in
// this class.
//
// This is a duplicate of testcase18.c and testcase19.c.


#include <assert.h>
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
	int i, n = 75000;
	char *str;
	ListyInt *listy;

	str = malloc(sizeof(char) * (n + 1));
	assert(str != NULL);

	for (i = 0; i < n; i++)
		str[i] = (i % 9 + 1) + '0';  // generate '1' through '9'
	str[n] = '\0';

	// Create, print, and destroy.
	listy = stringToListyInt(str);
	listyPrint(listy);
	destroyListyInt(listy);
	free(str);

	return 0;
}
