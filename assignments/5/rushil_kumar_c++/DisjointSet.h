#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "Edge.h"

class DisjointSet{
private:
    std::vector<int> sets;
    std::vector<int> heights;
    std::vector<Edge> edges;
    int numSets;
public:
    DisjointSet(int count, std::vector<Edge> edges);
    int find(int photo);
    void merge(int firstPhoto, int secondPhoto);
    void kruksallsAlgorithm();
    void printSets();
};

#endif
