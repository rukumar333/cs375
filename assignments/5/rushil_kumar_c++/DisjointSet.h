#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>
#include <string>

class DisjointSet{
private:
    std::vector<int> sets;
public:
    DisjointSet(int count);
    int find(int photo);
    void merge(int firstPhoto, int secondPhoto);
};

#endif
