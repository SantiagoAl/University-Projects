// Author: Alex Santiago

// ====================================
// ConstrainedTopoSort: TestCase01.cpp
// ====================================
// A small test case for ConstrainedTopoSort.

#include <iostream>
#include <string>

#include "ConstrainedTopoSort.h"

void failedTestCase(std::string params)
{
    std::cout << "Test Case #1: Failed on " << params << '\n';
}

int main(void)
{
    std::cout << std::boolalpha;

    ConstrainedTopoSort topo {"inputFiles/g1.txt"};

    if (topo.hasConstrainedTopoSort(1, 2) != true)
    {
        failedTestCase("1, 2");
        return 1;
    }

    if (topo.hasConstrainedTopoSort(1, 3) != true)
    {
        failedTestCase("1, 3");
        return 1;
    }

    if (topo.hasConstrainedTopoSort(1, 4) != true)
    {
        failedTestCase("1, 4");
        return 1;
    }

    std::cout << "Test Case #1: PASS (Horray!)" << '\n';

    return 0;
}
