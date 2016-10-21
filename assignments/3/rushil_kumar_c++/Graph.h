#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iostream>

class Graph{
public:
    Graph();
    Graph(int numCities);
    std::vector<std::vector<int> > weights;
    std::vector<std::string> cities;
    std::vector<std::vector<int > > intermediateNodes;
    void insertCity(std::string city);
    void insertWeight(std::string cityA, std::string cityB, int weight);
    std::vector<std::vector <int> > floydsAlgorithm(); 
    void printShortestPath(std::string start, std::string end);
    void printShortestPath(int startIndex, int endIndex);
};

#endif
