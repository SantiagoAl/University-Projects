// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase14.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] {1};
    int ans = 1;

    RunLikeHell hell {};

    if (hell.maxGain(blocks, 1) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}
