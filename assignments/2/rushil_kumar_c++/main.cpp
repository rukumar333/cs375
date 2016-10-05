#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>

class Point{
public:
    int x;
    int y;
    Point(int x, int y){
	this->x = x;
	this->y = y;	
    };
    Point& operator=(const Point& other){
	x = other.x;
	y = other.y;
	return *this;
    }
    
};
std::ostream& operator<<(std::ostream &os, const Point &point){
    os << "(" << point.x << "," << point.y << ")";
    return os;
}

double getDistance(Point p1, Point p2);
std::pair<int, int> getShortestDistance(std::vector<Point> points, int start, int end);


int main(int argc, char * argv[]){
    if(argc < 2){
	std::cout << "Need more arguments" << std::endl;
    }
    std::ifstream file(argv[1]);
    std::string str;
    std::vector<Point> points = std::vector<Point>();
    while(std::getline(file, str)){
	int x, y;
	std::string coord;
	std::stringstream ss;
	ss.str(str);
	std::getline(ss, coord, ' ');
	x = std::stoi(coord);
	std::getline(ss, coord, ' ');
	y = std::stoi(coord);
	points.push_back(Point(x, y));
    }
    std::sort(points.begin(), points.end(), [](Point p1, Point p2){
	    return p1.x < p2.x;
	});
    for(int i = 0; i < points.size(); ++ i){
	std::cout << points[i] << " ";
    }
    std::cout << std::endl;
    std::pair<int, int> indexPair = getShortestDistance(points, 0, points.size());    
}

double getDistance(Point p1, Point p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

std::pair<int, int> getShortestDistance(std::vector<Point> points, int start, int end){
    int length = end - start;
    if(length == 1){
	return std::make_pair(-1, -1);
    }
    if(length == 2){
	return std::make_pair(start, end);
    }
    //Split step
    int mid = (start + end) / 2;
    std::pair<int, int> leftPair = getShortestDistance(points, start, mid);
    std::pair<int, int> rightPair = getShortestDistance(points, mid, end);
    //Get minimum
    std::pair<int, int> minPair = std::pair<int, int>();
    double minDistance = 0;
    if(leftPair.first == -1){
	minPair = rightPair;
	minDistance = getDistance(points[minPair.first], points[minPair.second]);
    }
    if(rightPair.first == -1){
	minPair = leftPair;
	minDistance = getDistance(points[minPair.first], points[minPair.second]);
    }
    if(leftPair.first != -1 && rightPair.first != -1){
	double leftDistance = getDistance(points[leftPair.first], points[leftPair.second]);
	double rightDistance = getDistance(points[rightPair.first], points[rightPair.second]);
	if(leftDistance < rightDistance){
	    minPair = leftPair;
	    minDistance = leftDistance;
	}else{
	    minPair = rightPair;
	    minDistance = rightDistance;	    
	}
    }
    //Combine step
    
}
