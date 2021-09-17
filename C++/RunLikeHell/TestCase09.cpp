// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase09.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] { 17, 20, 111, 142, 88, 199, 86, 90, 199, 51, 174,
                    194, 3, 190, 138, 198, 104, 74, 195, 43};
    int ans = 1337;

    RunLikeHell hell {};

    if (hell.maxGain(blocks, 20) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}
