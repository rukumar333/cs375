#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <set>

class Graph{
public:
    std::vector<std::vector<int> > weights;
    std::set<std::string> cities;
    void insertCity(std::string city);
    void insertWeights(std::string city, std::vector<int> weights);
    void insertWeight(std::string cityA, std::string cityB, int weight);
    Graph();
    Graph(int numCities);
};

#endif
