// Author: Alex Santiago

// ====================================
// ConstrainedTopoSort: TestCase04.cpp
// ====================================
// A small test case for ConstrainedTopoSort.

#include <iostream>
#include <string>

#include "ConstrainedTopoSort.h"

void failedTestCase(std::string params)
{
    std::cout << "Test Case #4: Failed on " << params << '\n';
}

int main(void)
{
    std::cout << std::boolalpha;

    ConstrainedTopoSort topo {"inputFiles/g1.txt"};

    if (topo.hasConstrainedTopoSort(4, 1) != false)
    {
        failedTestCase("4, 1");
        return 1;
    }

    if (topo.hasConstrainedTopoSort(4, 2) != false)
    {
        failedTestCase("4, 2");
        return 1;
    }

    if (topo.hasConstrainedTopoSort(4, 3) != false)
    {
        failedTestCase("4, 3");
        return 1;
    }

    std::cout << "Test Case #4: PASS (Horray!)" << '\n';

    return 0;
}
