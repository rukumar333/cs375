#include "Graph.h"
#include <queue>
#include <iostream>

int Graph::findMinSemesters(){
    std::queue<int> fifo = std::queue<int>();
    std::vector<int> level = std::vector<int>(15, 1);
    // int root = 0;
    int semesterCount = 0;
    colors[0] = 1;
    colors[1] = 1;
    colors[2] = 1;
    // fifo.push(std::make_pair(0, 0));
    // fifo.push(std::make_pair(1, 0));
    // fifo.push(std::make_pair(2, 0));
    fifo.push(0);
    fifo.push(1);
    fifo.push(2);
    while(!fifo.empty()){
	// ++ semesterCount;
	int currentNode = fifo.front();
	if(semesterCount < level[currentNode]){
	    semesterCount = level[currentNode];
	}
	// std::cout << "Current: " << currentNode << std::endl;
	fifo.pop();
	// std::cout << "Popping: " << currentNode << std::endl;
	//Set node color to black
	// std::cout << "Setting color to black" << std::endl;
	colors[currentNode] = 1;
	// std::cout << "Setting color to black" << std::endl;
	for(int i = 0; i < matrix[currentNode].size(); ++ i){
	    //Check if edge and if color of node is white
	    // std::cout << "Checking: " << i << std::endl;
	    if(matrix[currentNode][i] == 1 && (colors[i] == 0 || level[i] < level[currentNode] + 1)){
		colors[i] = 1;
		fifo.push(i);
		level[i] = level[currentNode] + 1;
		// std::cout << currentNode + 1<< " " << i + 1<< std::endl;
		// std::cout << level[currentNode] << " " << level[i] << std::endl;
		// std::cout << std::endl;
	    }
	}
    }
    // std::cout << semesterCount << std::endl;
    return semesterCount;
}

Graph::Graph(std::vector<std::vector<bool> > input) : matrix(input){
    colors = std::vector<bool>(15, 0);
}

// Graph::Graph(){
//     matrix = std::vector<std::vector<bool> >(16, std::vector<bool>(16, 0));
//     // matrix[1][3] = 1;
//     // matrix[3][1] = 1;
//     // matrix[4][3] = 1;
//     // matrix[3][4] = 1;
//     // matrix[5][0] = 1;
//     // matrix[0][5] = 1;
//     // matrix[5][2] = 1;
//     // matrix[2][5] = 1;
//     // matrix[6][3] = 1;
//     // matrix[3][6] = 1;
//     // matrix[7][4] = 1;
//     // matrix[4][7] = 1;
//     // matrix[7][5] = 1;
//     // matrix[5][7] = 1;
//     // matrix[8][6] = 1;
//     // matrix[6][8] = 1;
//     // matrix[9][8] = 1;
//     // matrix[9][8] = 1;
//     // matrix[6][3] = 1;
//     // matrix[0][5] = 1;
//     // matrix[1][3] = 1;
    
//     // matrix = {
//     // 	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}	
//     // 	{0, 0, 0, 0, 0, 1}
//     // }
    
// }
