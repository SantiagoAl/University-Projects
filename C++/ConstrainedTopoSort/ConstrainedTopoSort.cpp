// Author: Alex Santiago

// This is a solution that I came up with for a programming assignment in
// Computer Science II. Originally the assignment was intended to be in the java
// programming language but I created this solution for it in C++

// This is the file that will be used when executing the TestCase files with the
// test-all.sh

#include "ConstrainedTopoSort.h"

// The classe's constructor reads in a graph from a file and initializes
// elements as appropriate
ConstrainedTopoSort::ConstrainedTopoSort(std::string filename)
    :matrix{nullptr}, incomingEdges{nullptr}, numVertices{0}
{
    // Create an input file stream to 'filename'
    std::ifstream inFile {filename};

    // First of all we have to check if the file was properly opened. If
    // not some crazy stuff might happen
    if (!inFile)
    {
        std::cerr << "Problem opening file" << '\n';
        return;
    }

    // Read in the number of vertices on the graph
    inFile >> this->numVertices;

    // Create an initialize the matrix and incomingEdges arrays dynamically
    initializeArrays();

    int j = 0;

    // We want to loop while we have not reached the 'end of file (eof)'
    while (!inFile.eof())
    {
        // Extract the numger of outgiong Edges at this vertex
        int numEdges;
        inFile >> numEdges;

        for (int i = 0; i < numEdges; i++)
        {
            // Read in the the vertices that this vertex points to, and
            // manipulate the arrays accordingly
            int edge;
            inFile >> edge;

            this->matrix[j][edge - 1] = true;
            this->incomingEdges[edge - 1]++;
        }

        j++;
    }

    inFile.close();
}

// Inside of the destructor of this class we want to free all of the
// dynamic memory associated with the object being destroyed
ConstrainedTopoSort::~ConstrainedTopoSort()
{
    // Loop through each index in the matrix and free all of the memory
    // that was created for each row
    for (int i{0}; i < this->numVertices; i++)
        delete [] this->matrix[i];

    // Finally free the 'matrix' and 'incomingEdges' pointers
    delete [] this->matrix;
    delete [] this->incomingEdges;
}

// This is a helper function used by the classe's constructor. It will initialize
// 'matrix' and 'incomingEdges' arrays before inserting data from the file in
// them. This is IMPORTANT as we do not want them to have garbage data, once we
// start inserting back in the constructor
void ConstrainedTopoSort::initializeArrays()
{
    // Dynamically create them according to the number of vertices
    this->incomingEdges = new int[this->numVertices];
    this->matrix = new bool *[this->numVertices];

    // For each index in the matrix, we want to create another array dynamically,
    // which it will be pointing too, giving us a 2-dimensional array
    for (int i{0}; i < this->numVertices; i++)
    {
        matrix[i] = new bool[this->numVertices];

        for (int j{0}; j < this->numVertices; j++)
            matrix[i][j] = false;
    }

    // Initiaize indices to zero in the incomingEdges array
    for (int i{0}; i < this->numVertices; i++)
        this->incomingEdges[i] = 0;
}

// This is the main function of the program. It will determine if the graph has
// a valid topological sort in which 'x' comes before 'y'
bool ConstrainedTopoSort::hasConstrainedTopoSort(int x, int y)
{
    // There is no valid topological sort if the graph contains a cycle.
    // Also if 'x' has no incomingEdges then there exists a valid topological
    // sort in which 'x' comes before 'y', return true. Lastly if 'x' and
    // 'y' are equal, return false
    if (hasCycle())
        return false;
    else if (this->incomingEdges[x - 1] == 0)
        return true;
    else if (x == y)
        return false;

    // A Queue to hold the next vertices to visit and a visited array for
    // the ones already visited
    std::queue<int> queue;
    bool visited [this->numVertices];

    // Initialize all indices to 'false'. Not doing so could cause an incorrect
    // output
    std::fill_n(visited, this->numVertices, false);

    queue.push(x - 1);
    visited[x - 1] = true;

    // Keep going as long as the Queue is no empty
    while (!queue.empty())
    {
        int vertex = queue.front();
        queue.pop();

        // If 'y' points to 'x' or a vertex that comes before 'x' then 'x'
        // cannot come before 'y', return false
        if (this->matrix[y - 1][vertex])
            return false;

        // Go through the graph and add to the Queue any vertices that point
        // to 'x' or that lead to 'x'
        for (int i = 0; i < this->numVertices; i++)
        {
            if (this->matrix[i][vertex] && !visited[i])
            {
                visited[i] = true;
                queue.push(i);
            }
        }
    }

    // Reaching this point means that there is a valid topological sort
    // where 'x' comes before 'y'
    return true;
}

// I use this method to determine if the graph has a cylce. If it contains a
// cycle, it returns true, false otherwise
bool ConstrainedTopoSort::hasCycle()
{
    bool visited[this->numVertices];
    int *incoming = new int[this->numVertices];

    std::copy(this->incomingEdges, this->incomingEdges + this->numVertices,
    incoming);
    std::queue<int> queue;

    // Add any vertices that with zero incoming edges to the Queue. We can
    // visit them
    for (int i = 0; i < this->numVertices; i++)
    {
        if (incoming[i] == 0)
            queue.push(i);
    }

    int count = 0;

    // Keep looping as long as the Queue is not Empty
    while(!queue.empty())
    {
        int vertex = queue.front();
        queue.pop();
        ++count;

        // Go to that vertex, if the outgoing edges to other vertices is zero
        // add them to the Queue and they can now be visited
        for (int i = 0; i < this->numVertices; i++)
        {
            if (this->matrix[vertex][i] && --incoming[i] == 0)
                queue.push(i);
        }
    }

    // If the count is not equal to the number of vertices then there is a
    // cycle, return true
    if (count != this->numVertices)
    {
        delete [] incoming;
        return true;
    }

    delete [] incoming;

    // Getting here means no cycle was detected, return false
    return false;
}

// This a method I used to the print the matrix to the console for debugging
// purposes
void ConstrainedTopoSort::printMatrix()
{
    for (int i = 0; i < this->numVertices; i++)
    {
        for (int j = 0; j < this->numVertices; j++)
            std::cout << this->matrix[i][j] << " ";

        std::cout << '\n';
    }
}
