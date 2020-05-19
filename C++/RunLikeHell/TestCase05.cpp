// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase05.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] {16, 10, 15, 12, 2, 20, 2, 16};
    int ans = 67;

    RunLikeHell hell {};

    if (hell.maxGain(blocks, 8) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}
