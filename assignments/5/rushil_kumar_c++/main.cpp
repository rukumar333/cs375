#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "Edge.h"
#include "DisjointSet.h"

int main(){
    std::ifstream file;
    file.open("input.txt");
    std::string line = "";
    std::vector<Edge> edges;
    while(std::getline(file, line)){
	Edge edge;
	std::string spaceSeparated = "";
	std::stringstream ss(line);	
	std::getline(ss, spaceSeparated, ' ');
	edge.first = std::stoi(spaceSeparated) - 1;
	std::getline(ss, spaceSeparated, ' ');
	edge.second = std::stoi(spaceSeparated) - 1;
	std::getline(ss, spaceSeparated, ' ');
	edge.weight = std::stoi(spaceSeparated);
	edges.push_back(edge);
    }
    DisjointSet disjoint(20, edges);
    disjoint.kruksallsAlgorithm();
    return 0;
}

