// Author: Alex Santiago

// ====================================
// RunLikeHell: TestCase13.cpp
// ====================================

#include <iostream>

#include "RunLikeHell.h"

void failTestCase()
{
    std::cout << "FAIL" << '\n';
}

int main(void)
{
    int blocks [] {};
    int ans = 0;

    RunLikeHell hell {};

    if (hell.maxGain(blocks, 0) != ans)
    {
        failTestCase();
        return 1;
    }

    std::cout << "PASS (Hooray!)" << '\n';

    return 0;
}
