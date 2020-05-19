// Sean Szumlanski
// COP 3502, Summer 2018

// ==============================
// LonelyPartyArray: testcase04.c
// ==============================
// Tests various aspects of set() functionality.


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
	LPA *party = createLonelyPartyArray(3, 12);

	// Call set() twice on same index.
	if (set(party, 14, 100) != LPA_SUCCESS)
		failwhale("(Err0.01) set() check failed.");
	if (set(party, 14, 100) != LPA_SUCCESS)
		failwhale("(Err0.02) set() check failed.");

	// Check whether the struct is set up correctly.
	if (party == NULL)
		failwhale("(Err1.01) NULL check failed.");
	if (party->size != 1)
		failwhale("(Err1.02) party->size check failed.");
	if (party->num_fragments != 3)
		failwhale("(Err1.03) party->num_fragments check failed.");
	if (party->fragment_length != 12)
		failwhale("(Err1.04) party->fragment_length check failed.");
	if (party->num_active_fragments != 1)
		failwhale("(Err1.05) party->num_active_fragments check failed.");
	if (party->fragments == NULL)
		failwhale("(Err1.06) party->fragments check failed.");
	if (party->fragment_sizes == NULL)
		failwhale("(Err1.07) party->fragment_sizes check failed.");

	for (i = 0; i < 3; i++)
	{
		if (i != 1 && party->fragments[i] != NULL)
			failwhale("(Err1.08a) party->fragments[i] check failed.");
		if (i == 1 && party->fragments[i] == NULL)
			failwhale("(Err1.08b) party->fragments[i] check failed.");
	}

	for (i = 0; i < 3; i++)
	{
		if (i != 1 && party->fragment_sizes[i] != 0)
			failwhale("(Err1.09a) party->fragment_sizes[i] check failed.");
		if (i == 1 && party->fragment_sizes[i] != 1)
			failwhale("(Err1.09b) party->fragment_sizes[i] check failed.");
	}

	for (i = 0; i < 12; i++)
	{
		if (i != 2 && party->fragments[1][i] != UNUSED)
			failwhale("(Err1.10a) party->fragment_sizes[1][i] check failed.");
		if (i == 2 && party->fragments[1][i] != 100)
			failwhale("(Err1.10b) party->fragment_sizes[1][i] check failed.");
	}

	// Also check that calling set() on invalid indices produces the correct
	// output and doesn't unsettle the struct's member values.
	if (set(party, 36, 100) != LPA_FAILURE)
		failwhale("(Err2.01) set() check failed.");
	if (set(party, 48, 100) != LPA_FAILURE)
		failwhale("(Err2.02) set() check failed.");
	if (set(party, 49, 100) != LPA_FAILURE)
		failwhale("(Err2.03) set() check failed.");
	if (set(party, 59, 100) != LPA_FAILURE)
		failwhale("(Err2.04) set() check failed.");

	// Check again that the struct is still set up correctly.
	if (party == NULL)
		failwhale("(Err3.01) NULL check failed.");
	if (party->size != 1)
		failwhale("(Err3.02) party->size check failed.");
	if (party->num_fragments != 3)
		failwhale("(Err3.03) party->num_fragments check failed.");
	if (party->fragment_length != 12)
		failwhale("(Err3.04) party->fragment_length check failed.");
	if (party->num_active_fragments != 1)
		failwhale("(Err3.05) party->num_active_fragments check failed.");
	if (party->fragments == NULL)
		failwhale("(Err3.06) party->fragments check failed.");
	if (party->fragment_sizes == NULL)
		failwhale("(Err3.07) party->fragment_sizes check failed.");

	for (i = 0; i < 3; i++)
	{
		if (i != 1 && party->fragments[i] != NULL)
			failwhale("(Err3.08a) party->fragments[i] check failed.");
		if (i == 1 && party->fragments[i] == NULL)
			failwhale("(Err3.08b) party->fragments[i] check failed.");
	}

	for (i = 0; i < 3; i++)
	{
		if (i != 1 && party->fragment_sizes[i] != 0)
			failwhale("(Err3.09a) party->fragment_sizes[i] check failed.");
		if (i == 1 && party->fragment_sizes[i] != 1)
			failwhale("(Err3.09b) party->fragment_sizes[i] check failed.");
	}

	for (i = 0; i < 12; i++)
	{
		if (i != 2 && party->fragments[1][i] != UNUSED)
			failwhale("(Err3.10a) party->fragment_sizes[1][i] check failed.");
		if (i == 2 && party->fragments[1][i] != 100)
			failwhale("(Err3.10b) party->fragment_sizes[1][i] check failed.");
	}

	destroyLonelyPartyArray(party);

	return 0;
}
