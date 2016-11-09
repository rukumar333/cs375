#include "Graph.h"
#include <queue>
#include <iostream>

int Graph::findMinSemesters(){
    std::queue<std::pair<int, int> fifo = std::queue<int>();    
    // int root = 0;
    int semesterCount = 0;
    colors[0] = 1;
    fifo.push(0);
    // colors[0] = ;
    // fifo.push(0);
    while(!fifo.empty()){
	++ semesterCount;
	int currentNode = fifo.front();
	std::cout << "Current: " << currentNode << std::endl;
	fifo.pop();
	// std::cout << "Popping: " << currentNode << std::endl;
	//Set node color to black
	// std::cout << "Setting color to black" << std::endl;
	colors[currentNode] = 1;
	// std::cout << "Setting color to black" << std::endl;
	for(int i = 0; i < matrix[currentNode].size(); ++ i){
	    //Check if edge and if color of node is white
	    // std::cout << "Checking: " << i << std::endl;
	    if(matrix[currentNode][i] == 1 && colors[i] == 0){
		colors[currentNode] = 1;
		fifo.push(i);
		std::cout << currentNode << " " << i << std::endl;
	    }
	}
    }
    std::cout << semesterCount << std::endl;
    return semesterCount;
}

Graph::Graph(std::vector<std::vector<bool> > input) : matrix(input){
    colors = std::vector<bool>(16, 0);
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
