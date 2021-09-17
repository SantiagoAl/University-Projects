// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase07.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] {7, 10, 18, 16, 17, 12, 14, 9};
    int ans = 56;

    RunLikeHell hell {};

    if (hell.maxGain(blocks, 8) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}
