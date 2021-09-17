// Author: Alex Santiago

// ====================================
// ConstrainedTopoSort: TestCase02.cpp
// ====================================
// A small test case for ConstrainedTopoSort.

#include <iostream>
#include <string>

#include "ConstrainedTopoSort.h"

void failedTestCase(std::string params)
{
    std::cout << "Test Case #2: Failed on " << params << '\n';
}

int main(void)
{
    std::cout << std::boolalpha;

    ConstrainedTopoSort topo {"inputFiles/g1.txt"};

    if (topo.hasConstrainedTopoSort(2, 1) != true)
    {
        failedTestCase("2, 1");
        return 1;
    }

    if (topo.hasConstrainedTopoSort(2, 3) != true)
    {
        failedTestCase("2, 3");
        return 1;
    }

    if (topo.hasConstrainedTopoSort(2, 4) != true)
    {
        failedTestCase("2, 4");
        return 1;
    }

    std::cout << "Test Case #2: PASS (Horray!)" << '\n';

    return 0;
}
