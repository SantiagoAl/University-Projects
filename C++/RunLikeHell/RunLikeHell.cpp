// This program is my solution to a programming assignment in Computer Science 2
// For the assignment we had to come up with a Dynamic Programming solution
// The program is called Run Like Hell and the specifics of the program can be
// seen in 'RunLikeHell.pdf'

#include "RunLikeHell.h"

// A simple helper function that returns the max of two integers
int RunLikeHell::max(int x, int y)
{
    return (x > y) ? x : y;
}

// This method returns the maximum amount of knowledge that the aglorithmist
// can gain before getting off the mountain
int RunLikeHell::maxGain(int *blocks, int size)
{
    if (blocks == nullptr)
        return 0;

    // When initializng the array I make sure it has at least one index
    int length = max(size, 1);
    int *maxResult = new int[length];
    std::fill_n(maxResult, length, 0);

    // This takes into account if the array passed to the method is empty
    maxResult[0] = size > 0 ? blocks[0] : 0;

    int i;

    // Iterate through the knowledge blocks while calculating and storing
    // the max results
    for (i = 1; i < size; i++)
    {
        // If this is the first pass then find the max of the first index in
        // 'maxResult' or the first index of block
        if ((i - 1) == 0)
        {
            maxResult[i] = max(maxResult[i - 1], 0 + blocks[i]);
        }
        // If its not the first pass, then this index is the max of the
        // result just before it, or the result 2 indices before it plus the
        // value at this index in 'blocks'
        else
        {
            maxResult[i] = max(
                maxResult[i - 1], maxResult[i - 2] + blocks[i]
            );
        }
    }

    int maxGain = maxResult[i - 1];

    delete [] maxResult;

    return maxGain;
}
