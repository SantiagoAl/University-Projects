// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase01.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] {15, 3, 6, 17, 2, 1, 20};
    int ans = 52;

    RunLikeHell hell {};

    if (hell.maxGain(blocks, 7) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}
