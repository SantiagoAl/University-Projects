// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase06.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] {3, 5, 7, 3, 11, 5, 9, 8};
    int ans = 30;

    RunLikeHell hell {};

    if (hell.maxGain(blocks, 8) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}
