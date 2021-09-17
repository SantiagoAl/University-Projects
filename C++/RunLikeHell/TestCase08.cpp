// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase08.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] {573, 216, 451, 236, 42, 243, 743, 162, 317, 323, 4,
                   407, 230, 380, 177, 89, 596, 421, 643, 655, 735, 441,
                   408, 716, 449, 781, 28, 346, 241, 229, 697, 354, 685,
                   628, 535, 463, 578, 275, 786, 362, 488, 372, 68, 434,
                   687};
    int ans = 11260;

    RunLikeHell hell {};

    if (hell.maxGain(blocks, 45) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}
