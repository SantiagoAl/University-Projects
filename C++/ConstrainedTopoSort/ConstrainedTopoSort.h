#ifndef _CONSTRAINED_TOPO_SORT_H_
#define _CONSTRAINED_TOPO_SORT_H_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>

class ConstrainedTopoSort
{
private:
    bool **matrix;
    int *incomingEdges;
    int numVertices;
public:
    // Class constructor
    ConstrainedTopoSort(std::string filename);

    void initializeArrays();
    bool hasConstrainedTopoSort(int x, int y);
    bool hasCycle();
    void printMatrix();

    // Class Destructor
    ~ConstrainedTopoSort();
};

#endif // _CONSTRAINED_TOPO_SORT_H_
