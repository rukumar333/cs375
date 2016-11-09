#include "Graph.h"
#include <queue>
#include <iostream>

int Graph::findMinSemesters(){
    std::queue<int> fifo = std::queue<int>();
    std::vector<int> level = std::vector<int>(15, 1);
    int semesterCount = 0;
    colors[0] = 1;
    colors[1] = 1;
    colors[2] = 1;
    fifo.push(0);
    fifo.push(1);
    fifo.push(2);
    while(!fifo.empty()){
	int currentNode = fifo.front();
	if(semesterCount < level[currentNode]){
	    semesterCount = level[currentNode];
	}
	fifo.pop();
	colors[currentNode] = 1;
	for(int i = 0; i < matrix[currentNode].size(); ++ i){
	    //Check if edge and if color of node is white
	    if(matrix[currentNode][i] == 1 && (colors[i] == 0 || level[i] < level[currentNode] + 1)){
		colors[i] = 1;
		fifo.push(i);
		level[i] = level[currentNode] + 1;
	    }
	}
    }
    return semesterCount;
}

Graph::Graph(std::vector<std::vector<bool> > input) : matrix(input){
    colors = std::vector<bool>(15, 0);
}
