#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Graph.h"

int main(){
    // std::cout << std::stoi("cs15") << std::endl;
    std::ifstream file("input.txt");
    std::vector<std::vector<bool> > matrix = std::vector<std::vector<bool> >(15, std::vector<bool>(15, 0));
    std::string temp = "";
    while(std::getline(file, temp)){
	std::stringstream ss(temp);
	std::string course = "";
	std::getline(ss, course, ' ');
	int endCourse = std::stoi(course) - 1;
	while(std::getline(ss, course, ' ')){
	    int startCourse = std::stoi(course) - 1;
	    // matrix[endCourse][startCourse] = 1;
	    matrix[startCourse][endCourse] = 1;
	    // std::cout << endCourse << " " << startCourse << std::endl;
	}
    }
    Graph graph = Graph(matrix);
    std::cout << graph.findMinSemesters() << std::endl;
}
