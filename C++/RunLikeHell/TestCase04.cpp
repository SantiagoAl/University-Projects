// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase04.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] {1, 15, 3, 6, 17, 2, 1, 20};
    int ans = 52;

    RunLikeHell hell {};

    if (hell.maxGain(blocks, 8) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}
