// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase03.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] {9, 20, 13, 16, 9, 6, 9};
    int ans = 45;

    RunLikeHell hell {};

    if (hell.maxGain(blocks, 7) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}
