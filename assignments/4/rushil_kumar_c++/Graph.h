#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

class Graph{
private:
    std::vector<std::vector<bool> > matrix;
    std::vector<bool> colors;
public:
    Graph(std::vector<std::vector<bool> > input);
    int findMinSemesters();
};

#endif
