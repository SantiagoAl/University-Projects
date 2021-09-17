// Sean Szumlanski
// COP 3502, Summer 2018

// ==============================
// LonelyPartyArray: testcase01.c
// ==============================
// Basic check to ensure createLonelyPartyArray() is initializing everything
// correctly.


#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

// This function exist with status 0 so as not to give a false indication of a
// segmentation fault.
void failwhale(char *err_msg)
{
	printf("[failwhale]: %s\n", err_msg);
	exit(0);
}

int main(void)
{
	int i;
	int num_fragments = 12;
	int fragment_length = 3;

	LPA *party = createLonelyPartyArray(num_fragments, fragment_length);

	if (party == NULL)
		failwhale("(Err01) NULL check failed.");
	if (party->size != 0)
		failwhale("(Err02) party->size check failed.");
	if (party->num_fragments != num_fragments)
		failwhale("(Err03) party->num_fragments check failed.");
	if (party->fragment_length != fragment_length)
		failwhale("(Err04) party->fragment_length check failed.");
	if (party->num_active_fragments != 0)
		failwhale("(Err05) party->num_active_fragments check failed.");
	if (party->fragments == NULL)
		failwhale("(Err06) party->fragments check failed.");
	if (party->fragment_sizes == NULL)
		failwhale("(Err07) party->fragment_sizes check failed.");

	for (i = 0; i < num_fragments; i++)
		if (party->fragments[i] != NULL)
			failwhale("(Err08) party->fragments[i] check failed.");

	for (i = 0; i < num_fragments; i++)
		if (party->fragment_sizes[i] != 0)
			failwhale("(Err09) party->fragment_sizes[i] check failed.");

	destroyLonelyPartyArray(party);

	return 0;
}
