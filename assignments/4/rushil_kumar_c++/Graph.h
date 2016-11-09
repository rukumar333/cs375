#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

class Graph{
private:
    std::vector<std::vector<bool> > matrix;
    std::vector<bool> colors;
public:
    Graph(std::vector<std::vector<bool> > input);//  : matrix(input){
    // 	std::vector<bool> colors = std::vector<bool>(16, 0);       
    // 	colors[0] = 1;
    // 	std::cout << "In here " << std::endl;
    // };
    int findMinSemesters();
};

#endif
