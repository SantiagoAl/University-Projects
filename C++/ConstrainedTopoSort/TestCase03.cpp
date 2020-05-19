// Author: Alex Santiago

// ====================================
// ConstrainedTopoSort: TestCase03.cpp
// ====================================
// A small test case for ConstrainedTopoSort.

#include <iostream>
#include <string>

#include "ConstrainedTopoSort.h"

void failedTestCase(std::string params)
{
    std::cout << "Test Case #3: Failed on " << params << '\n';
}

int main(void)
{
    std::cout << std::boolalpha;

    ConstrainedTopoSort topo {"inputFiles/g1.txt"};

    if (topo.hasConstrainedTopoSort(3, 1) != false)
    {
        failedTestCase("3, 1");
        return 1;
    }

    if (topo.hasConstrainedTopoSort(3, 2) != false)
    {
        failedTestCase("3, 2");
        return 1;
    }

    if (topo.hasConstrainedTopoSort(3, 4) != true)
    {
        failedTestCase("3, 4");
        return 1;
    }

    std::cout << "Test Case #3: PASS (Horray!)" << '\n';

    return 0;
}
