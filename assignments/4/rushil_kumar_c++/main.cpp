#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Graph.h"

double linearProgramming();
double simplexMethod(std::vector<std::vector<double > > &matrix);
void printMatrix(std::vector<std::vector<double > > &matrix);

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
	    matrix[startCourse][endCourse] = 1;
	}
    }
    Graph graph = Graph(matrix);
    std::cout << "Minimum number of semesters: " << graph.findMinSemesters() << std::endl;
    std::cout << "Cents: " << linearProgramming() << std::endl;
}

double linearProgramming(){
    std::vector<std::vector<double > > matrix = {
	{60, 60, 1, 0, 0, 300},
	{12, 6, 0, 1, 0, 36},
	{10, 30, 0, 0, 1, 90},
	{-12, -15, 0, 0, 0, 0}
    };
    return simplexMethod(matrix);
}

double extraCredit(){
    // std::vector<std::vector<double> > matrix = {
    // 	{}
    // }
}

double simplexMethod(std::vector<std::vector<double > > &matrix){
    int x = matrix.size();
    int y = matrix[0].size();
    int pivotColumn = -1;
    // int length = matrix[matrix.size() - 1];
    for(int i = 0; i < y; ++ i){
	if(pivotColumn != -1 && matrix[x - 1][i] < matrix[x - 1][pivotColumn]){
	    pivotColumn = i;
	}else{
	    if(pivotColumn == -1 && matrix[x - 1][i] < 0)
		pivotColumn = i;
	}
    }
    if(pivotColumn == -1){
	return matrix[x - 1][y - 1];
    }
    int pivotRow = -1;
    double dividedNum = 0;
    for(int i = 0; i < x - 1; ++ i){
	double tempNum = matrix[i][y - 1] / matrix[i][pivotColumn];
	if(pivotRow == -1 && tempNum > 0){
	    dividedNum = tempNum;
	    pivotRow = i;
	}else{
	    if(dividedNum > tempNum && tempNum > 0){
		dividedNum = tempNum;
		pivotRow = i;
	    }
	}
    }
    //Divide by pivot element
    double pivotElement = matrix[pivotRow][pivotColumn];
    for(int i = 0; i < y; ++ i){
	matrix[pivotRow][i] = matrix[pivotRow][i] / pivotElement;
    }    
    //Cancel other rows out
    for(int i = 0; i < x; ++ i){
	if(i != pivotRow){
	    double mult = matrix[i][pivotColumn];
	    for(int j = 0; j < y; ++ j){
		matrix[i][j] = matrix[i][j] - (mult * matrix[pivotRow][j]);
	    }
	}
    }
    // std::cout << pivotColumn << std::endl;
    // std::cout << pivotRow << std::endl;
    return simplexMethod(matrix);
}

void printMatrix(std::vector<std::vector<double > > &matrix){
    for(int i = 0; i < matrix.size(); ++ i){
	for(int j = 0; j < matrix[i].size(); ++ j){
	    std::cout << matrix[i][j] << " ";
	}
	std::cout << std::endl;
    }
}
