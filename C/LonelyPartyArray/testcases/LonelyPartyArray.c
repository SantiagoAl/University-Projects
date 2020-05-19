// Alex Santiago
// NID: al625608
// COP 3502, Summer 2018

#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

int find_fragment_num(LonelyPartyArray *party, int index);
int find_fragment_cell(LonelyPartyArray *party, int index);

// This function creates a new LonelyPartyArray
LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length){

	int i, m;

	if(num_fragments <= 0 || fragment_length <= 0){
		return NULL;
	}

	m = num_fragments * fragment_length;
    
    LPA *s = malloc(sizeof(LPA));

	if(s == NULL){
		return NULL;
	}

	s->num_fragments = num_fragments;
	s->fragment_length = fragment_length;
	s->num_active_fragments = 0;
	s->size = 0;

	s->fragments = malloc(sizeof(int *) * num_fragments);

	if(s->fragments == NULL){
		printf("Error when using malloc for the fragments array\n");
		free(s);
		return NULL;
	}

	for(i = 0; i < num_fragments; i++){
		s->fragments[i] = NULL;
	}

	s->fragment_sizes = malloc(sizeof(int) * num_fragments);

	if(s->fragment_sizes == NULL){
		printf("Error when using malloc for fragments_sizes\n");
		free(s);
		free(s->fragments);
		return NULL;
	}

	for(i = 0; i < num_fragments; i++){
		s->fragment_sizes[i] = 0;
	}

	printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", m, s->num_fragments);

	return s;
}

// This function frees up any memory associated with the LonelyPartyArray
LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party){

    int i;
  
	if(party == NULL){
        return NULL;
    }
    // This for loop will free the individual fragments that have been allocated
	for(i = 0; i < party->num_fragments; i++){
		if(party->fragments[i] != NULL){
				free(party->fragments[i]);
		}
	}

    free(party->fragments);
	free(party->fragment_sizes);
	free(party);

	printf("-> The LonelyPartyArray has returned to the void.\n");
    
	return NULL;
}

// This function makes a copy of the LonelyPartyArray
LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party){

    int i, j, x;
    
    if(party == NULL){
        return NULL;
    }
    
    LPA *new_party = malloc(sizeof(LPA));
    
    if(new_party == NULL){
        printf("Error when calling malloc in clone()\n");
        return NULL;
    }
    
    new_party->num_fragments = party->num_fragments;
    new_party->fragment_length = party->fragment_length;
    new_party->size = party->size;
    new_party->num_active_fragments = party->num_active_fragments;

    new_party->fragments = malloc(sizeof(int*) * new_party->num_fragments);
    
    if(new_party->fragments == NULL){
        printf("Error when calling malloc in clone()\n");
        return NULL;
    }
    
    x = new_party->num_fragments * new_party->fragment_length;
    
    // This for loop initializes the the pointers in the fragments array to NULL
    // and dynamically allocates any of the individual fragments if they had been
    // allocated in the original LPA struct
    for(i = 0; i < new_party->num_fragments; i++){
        new_party->fragments[i] = NULL;
        if(party->fragments[i] != NULL){
            new_party->fragments[i] = malloc(sizeof(int) * new_party->fragment_length);
            if(new_party->fragments[i] == NULL){
                printf("Error when calling malloc in clone()\n");
                return NULL;
            }
        }
    }
    
    new_party->fragment_sizes = malloc(sizeof(int) * new_party->num_fragments);
    if(new_party->fragment_sizes == NULL){
        printf("Error when calling malloc in clone()\n");
        return NULL;
    }
    // This for loop copies the fragment_sizes array, as well as copies any individual array fragments
    // that have been allocated
    for(i = 0; i < new_party->num_fragments; i++){
        new_party->fragment_sizes[i] = party->fragment_sizes[i];
        if(party->fragment_sizes[i] != 0){
            for(j = 0; j < new_party->fragment_length; j++){
                new_party->fragments[i][j] = party->fragments[i][j];
            }
        }
    }
    
    printf("-> Successfully cloned the LonelyPartyArray. (capacity: %d, fragments: %d)\n", x, new_party->num_fragments);
    
	return new_party;
}

// This function takes the index parameter and stores key in the appropriate fragment and cell
int set(LonelyPartyArray *party, int index, int key){

    int i;
    int fragment_num, frag_index;
    int q, r, s, M, N;
    int x;
    
    if(party == NULL){
        printf("-> Bloop! NULL pointer detected in set().\n");
        return LPA_FAILURE;
    }

	x = party->num_fragments * party->fragment_length - 1;
	q = party->fragment_length;

    fragment_num = find_fragment_num(party, index);
    frag_index = find_fragment_cell(party, index);

	r = party->fragment_length * fragment_num;
	s = ((party->fragment_length * fragment_num) + party->fragment_length) - 1;

    if(index > x || index < 0){
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, fragment_num, frag_index);
		return LPA_FAILURE;
	}

	if(party->fragments[fragment_num] == NULL){
		party->fragments[fragment_num] = malloc(sizeof(int) * party->fragment_length);
		if(party->fragments[fragment_num] == NULL){
			return LPA_FAILURE;
		}else{
			for(i = 0; i < party->fragment_length; i ++ ){
				party->fragments[fragment_num][i] = UNUSED;
        }
    }
    party->num_active_fragments++;
    printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", fragment_num, q, r, s);	}

	if(party->fragments[fragment_num][frag_index] == UNUSED){
		party->fragments[fragment_num][frag_index] = key;
		party->fragment_sizes[fragment_num]++;
		party->size++;
	}else{
		party->fragments[fragment_num][frag_index] = key;
	}
    
	return LPA_SUCCESS;
}

// This function gets the value stored at the index
int get(LonelyPartyArray *party, int index){

    int x;
    int fragment_num, frag_index;
    
    if(party == NULL){
        printf("-> Bloop! NULL pointer detected in get().\n");
        return LPA_FAILURE;
    }

	x = party->num_fragments * party->fragment_length - 1;

    fragment_num = find_fragment_num(party, index);
    frag_index = find_fragment_cell(party, index);

    if(index > x || index < 0){
		printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, fragment_num, frag_index);
		return LPA_FAILURE;
	}

	if(party->fragments[fragment_num] == NULL){
		return UNUSED;
	}

	return party->fragments[fragment_num][frag_index];
}

// This function deletes the value stored at the appropriate index
int delete(LonelyPartyArray *party, int index){

    int fragment_num, frag_index;
    int x, q, r, s, i;
    
    if(party == NULL){
        printf("-> Bloop! NULL pointer detected in delete().\n");
        return LPA_FAILURE;
    }
    
	x = party->num_fragments * party->fragment_length - 1;
	q = party->fragment_length;

    fragment_num = find_fragment_num(party, index);
    frag_index = find_fragment_cell(party, index);

    r = party->fragment_length * fragment_num;
	s = ((party->fragment_length * fragment_num) + party->fragment_length) - 1;

    if(index > x || index < 0){
		printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, fragment_num, frag_index);
		return LPA_FAILURE;
	}

	if(party->fragments[fragment_num] == NULL){
		return LPA_FAILURE;
	}

	if(party->fragments[fragment_num][frag_index] == UNUSED){
		return LPA_FAILURE;
	}else{
		party->fragments[fragment_num][frag_index] = UNUSED;
		party->size--;
		party->fragment_sizes[fragment_num]--;
	}

	if(party->fragment_sizes[fragment_num] == 0){
		free(party->fragments[fragment_num]);
		party->fragments[fragment_num] = NULL;
        party->num_active_fragments--;
		printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", fragment_num, q, r, s);
	}

	return LPA_SUCCESS;
}

// This function loops through the LPA to find if it contains the key
int containsKey(LonelyPartyArray *party, int key){

	int i, j;

	if(party == NULL){
		return 0;
	}

    
    for(i = 0; i < party->num_fragments; i++){
        if(party->fragments[i] != NULL){
            for(j = 0; j < party->fragment_length; j++){
                if(party->fragments[i][j] == key){
                    return 1;
                }
            }
        }
    }

	return 0;
}

// This function determines if a value other than UNUSED is stored at the index
int isSet(LonelyPartyArray *party, int index){

	int fragment_num, frag_index;
	int x;
    
    if(party == NULL){
        return 0;
    }
    
	x = party->num_fragments * party->fragment_length - 1;

	if(index > x || index < 0){
		return 0;
	}
    
    fragment_num = find_fragment_num(party, index);
	frag_index = index % party->fragment_length;

	if(party->fragments[fragment_num] == NULL){
		return 0;
	}else if(party->fragments[fragment_num][frag_index] == UNUSED){
		return 0;
	}else{
		return 1;
	}

}

// This function printf the value stored at index if it is valid
int printIfValid(LonelyPartyArray *party, int index){

    int fragment_num, frag_index;
    int x, value;
    
    if(party == NULL){
        return LPA_FAILURE;
    }

	x = party->num_fragments * party->fragment_length - 1;

    fragment_num = find_fragment_num(party, index);
    frag_index = find_fragment_cell(party, index);

	if(index > x || index < 0){
		return LPA_FAILURE;
	}

	if(party->fragments[fragment_num] == NULL){
		return LPA_FAILURE;
	}
    
    if(party->fragments[fragment_num][frag_index] == UNUSED){
        return LPA_FAILURE;
    }

	value = party->fragments[fragment_num][frag_index];

	printf("%d\n", value);

	return LPA_SUCCESS;
}

// This function will revert the LPA back to it's initial state
LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party){

    int i, j, y;
    int capacity;
    
    if(party == NULL){
        printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
        return 0;
    }
    
	capacity = party->num_fragments * party->fragment_length;

	for(i = 0; i < party->num_fragments; i++){
		if(party->fragments[i] != NULL){
			free(party->fragments[i]);
			party->fragments[i] = NULL;
		}
	}

	for(i = 0; i < party->num_fragments; i++){
		party->fragment_sizes[i] = 0;
	}

	party->size = 0;
	party->num_active_fragments = 0;

	if(party != NULL){
		printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", capacity, party->num_fragments);
	}

	return party;
}

// This function returns the nunber of elements currently in LonelyPartyArray
int getSize(LonelyPartyArray *party){

	if(party == NULL){
		return -1;
	}
    
	return party->size;
}

// This function returns the maximum number of elements that LonleyPartyArray can hold
int getCapacity(LonelyPartyArray *party){

	if(party == NULL){
		return -1;
	}
    
	return party->num_fragments * party->fragment_length;
}

// This function will return the number of elements it can hold with only the fragments that have been allocated
int getAllocatedCellCount(LonelyPartyArray *party){

	int temp, i;

	if(party == NULL){
		return -1;
	}

	temp = 0;

	for(i = 0; i < party->num_fragments; i++){
		if(party->fragments[i] != NULL){
			temp += party->fragment_length;
		}
	}

	return temp;
}

// This function shows the amount of bytes a traditional array would have taken up
long long unsigned int getArraySizeInBytes(LonelyPartyArray *party){

	int num_fragments, fragment_length;
	long long unsigned int temp, array_bytes;

	if(party == NULL){
		return 0;
	}

	num_fragments = party->num_fragments;
	fragment_length = party->fragment_length;

	temp = (long long unsigned int)num_fragments * fragment_length;

	array_bytes = sizeof(int) * temp;

	return array_bytes;
}

// This function shows the amount of bytes taken up by our LPA
long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party){

    long long unsigned int current_size;
    int temp1, temp2, temp3, temp4;
    int i, j;

    
    if(party == NULL){
        return 0;
    }
    
    temp1 = sizeof(LPA*) + sizeof(LPA);
    
    temp2 = 0;
    temp4 = 0;
	for(i = 0; i < party->num_fragments; i++){
        if(party->fragments[i] != NULL){
            for(j = 0; j < party->fragment_length; j++){
                temp2 += sizeof(party->fragments[i][j]);
            }
        }
        temp4 += sizeof(party->fragments[i]);
    }

    temp3 = 0;
	for(j = 0; j < party->num_fragments; j++){
        temp3 += sizeof(party->fragment_sizes[j]);
    }

    current_size = (long long unsigned int)temp1 + temp2 + temp3 + temp4;

	return current_size;
}
// This functions returns the fragment number that index maps to
int find_fragment_num(LonelyPartyArray *party, int index){
    
    int fragment_num;
    
    fragment_num = index / party->fragment_length;
    
    return fragment_num;
}
// This function returns the fragment cell index maps to
int find_fragment_cell(LonelyPartyArray *party, int index){
    
    int frag_index;
   
    if(index < 0){
        frag_index = index % -(party->fragment_length);
    }else{
        frag_index = index % party->fragment_length;
    }
   
    return frag_index;
}

// This is how difficult I found LonelyPartyArray
double difficultyRating(void){
	return 4.00;
}

//The estimated amount of hours I spent on LonelyPartyArray
double hoursSpent(void){
	return 35.00;
}
