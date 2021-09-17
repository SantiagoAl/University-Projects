// Sean Szumlanski
// COP 3502, Summer 2018

// =========================================
// LonelyPartyArray: valgrind-test03-bonus.c
// =========================================
// Tests the functionality of cloneLonelyPartyArray(). This is a bonus test
// case.


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

// Check the struct contents and call failwhale() if anything is out of sorts.
void party_check(LonelyPartyArray *party)
{
	int i;
	int num_fragments = 14;
	int fragment_length = 8;

	// Check struct setup.
	if (party == NULL)
		failwhale("(Err1.01) NULL check failed.");
	if (party->size != 6)
		failwhale("(Err1.02) party->size check failed.");
	if (party->num_fragments != 14)
		failwhale("(Err1.03) party->num_fragments check failed.");
	if (party->fragment_length != 8)
		failwhale("(Err1.04) party->fragment_length check failed.");
	if (party->num_active_fragments != 5)
		failwhale("(Err1.05) party->num_active_fragments check failed.");
	if (party->fragments == NULL)
		failwhale("(Err1.06) party->fragments check failed.");
	if (party->fragment_sizes == NULL)
		failwhale("(Err1.07) party->fragment_sizes check failed.");

	// Check fragments. Only fragments 4, 10, 11, 12, and 13 should be active.
	for (i = 0; i < num_fragments; i++)
	{
		if ((i != 4 && i != 10 && i != 11 && i != 12 && i != 13) && party->fragments[i] != NULL)
			failwhale("(Err1.08a) party->fragments[i] check failed.");
		if ((i == 4 || i == 10 || i == 11 || i == 12 || i == 13) && party->fragments[i] == NULL)
			failwhale("(Err1.08b) party->fragments[i] check failed.");
	}
	// Check contents of fragment 4.
	for (i = 0; i < fragment_length; i++)
	{
		if (i != 2 && party->fragments[4][i] != UNUSED)
			failwhale("(Err1.09a) party->fragments[i] check failed.");
		if (i == 2 && party->fragments[4][i] != 1)
			failwhale("(Err1.09b) party->fragments[i] check failed.");
	}
	// Check contents of fragment 10.
	for (i = 0; i < fragment_length; i++)
	{
		if (i != 3 && party->fragments[10][i] != UNUSED)
			failwhale("(Err1.10a) party->fragments[i] check failed.");
		if (i == 3 && party->fragments[10][i] != 2)
			failwhale("(Err1.10b) party->fragments[i] check failed.");
	}
	// Check contents of fragment 11.
	for (i = 0; i < fragment_length; i++)
	{
		if ((i != 4 && i != 7) && party->fragments[11][i] != UNUSED)
			failwhale("(Err1.11a) party->fragments[i] check failed.");
		if (i == 4 && party->fragments[11][i] != 5)
			failwhale("(Err1.11b) party->fragments[i] check failed.");
		if (i == 7 && party->fragments[11][i] != 8)
			failwhale("(Err1.11c) party->fragments[i] check failed.");
	}
	// Check contents of fragment 12.
	for (i = 0; i < fragment_length; i++)
	{
		if (i != 2 && party->fragments[12][i] != UNUSED)
			failwhale("(Err1.12a) party->fragments[i] check failed.");
		if (i == 2 && party->fragments[12][i] != 6)
			failwhale("(Err1.11d) party->fragments[i] check failed.");
	}
	// Check contents of fragment 13.
	for (i = 0; i < fragment_length; i++)
	{
		if (i != 5 && party->fragments[13][i] != UNUSED)
			failwhale("(Err1.12a) party->fragments[i] check failed.");
		if (i == 5 && party->fragments[13][i] != 3)
			failwhale("(Err1.12b) party->fragments[i] check failed.");
	}
}


int main(void)
{
	LPA *party = createLonelyPartyArray(14, 8);
	LPA *clone;

	// Set a few elements.
	set(party, 34, 1);
	set(party, 83, 2);
	set(party, 92, 5);
	set(party, 95, 8);
	set(party, 98, 6);
	set(party, 109, 3);

	// Check structure and contents of the original lonely party array.
	party_check(party);

	// Clone the party array.
	clone = cloneLonelyPartyArray(party);

	// Check structure and contents of the clone.
	party_check(clone);

	// Check that the structure and contents of the original have survived.
	party_check(party);

	// Ensure that clone is not simply referring to the original lonely party
	// array or any of its constituent members.
	if (clone == party)
		failwhale("(Err2.00) clone == party.");
	if (clone->fragments == party->fragments)
		failwhale("(Err3.01) clone->fragments == party->fragments.");
	if (clone->fragment_sizes == party->fragment_sizes)
		failwhale("(Err3.02) clone->fragment_sizes == party->fragment_sizes.");

	if (clone->fragments[4] == party->fragments[4])
		failwhale("(Err3.01) clone->fragments[4] == party->fragments[4].");
	if (clone->fragments[10] == party->fragments[10])
		failwhale("(Err3.01) clone->fragments[10] == party->fragments[10].");
	if (clone->fragments[11] == party->fragments[11])
		failwhale("(Err3.01) clone->fragments[11] == party->fragments[11].");
	if (clone->fragments[12] == party->fragments[12])
		failwhale("(Err3.01) clone->fragments[12] == party->fragments[12].");
	if (clone->fragments[13] == party->fragments[13])
		failwhale("(Err3.01) clone->fragments[13] == party->fragments[13].");

	destroyLonelyPartyArray(party);
	destroyLonelyPartyArray(clone);

	return 0;
}
