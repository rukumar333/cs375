#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>

class Point{
public:
    int x = 0;
    int y = 0;
    int z = 0;
    int numCoordinates = 0;
    Point(int x, int y, int z, int numCoordinates, int index){
	this->x = x;
	this->y = y;
	this->z = z;
	this->numCoordinates = numCoordinates;
	this->index = index;
    };
    Point& operator=(const Point& other){
	x = other.x;
	y = other.y;
	z = other.z;
	numCoordinates = other.numCoordinates;
	index = other.index;
	return *this;
    }
    int index = -1;
    
};
std::ostream& operator<<(std::ostream &os, const Point &point){
    os << "(" << point.x << "," << point.y << "," << point.z << ")";
    return os;
}

double getDistance(Point p1, Point p2);
std::pair<int, int> getShortestDistance(std::vector<Point> points);
std::pair<int, int> getShortestRec(const std::vector<Point> &points, int start, int end, std::vector<int> &mergedPointsIndices);
void mergeYSorted(const std::vector<Point> &points, std::vector<int> &mergedPointsIndices, std::vector<int> &leftMergedIndices, std::vector<int> &rightMergedIndices);
std::pair<int, int> getMiddlePair(const std::vector<Point> &points, std::vector<int> mergedPointsIndices, double minDistance, int middleY);
std::pair<int, int> getShortestDistanceIter(const std::vector<Point> &points);


int main(int argc, char * argv[]){
    if(argc < 3){
	std::cout << "Need more arguments" << std::endl;
	return 0;
    }
    //Parsing input
    std::ifstream file(argv[1]);
    std::string str;
    std::vector<Point> points = std::vector<Point>();
    while(std::getline(file, str)){
	int x = 0;
	int y = 0;
	int z = 0;
	int i = 0;
	std::string coord;
	std::stringstream ss;
	ss.str(str);
	while(std::getline(ss, coord, ' ')){
	    switch(i){
	    case 0:
		x = std::stoi(coord);
		break;
	    case 1:
		y = std::stoi(coord);
		break;
	    case 2:
		z = std::stoi(coord);
		break;
	    }
	    ++ i;
	}
	points.push_back(Point(x, y, z, i, points.size()));
    }
    //Getting shortest distance
    //Code to test time difference in DC and Brute Force
    // std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    // std::pair<int, int> indexPair = getShortestDistance(points);
    // std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    // auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    // std::cout << points[indexPair.first] << " " << points[indexPair.second] << std::endl;
    // std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
    // std::pair<int, int> indexPairIter = getShortestDistanceIter(points);
    // std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
    // auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( t4 - t3 ).count();
    // std::cout << points[indexPairIter.first] << " " << points[indexPairIter.second] << std::endl;
    // std::cout << "Recursive DC: " << duration1 << std::endl;
    // std::cout << "Iteration: " << duration2 << std::endl;
    std::ofstream outputFile(argv[2]);
    std::pair<int, int> indexPair = getShortestDistance(points);
    std::cout << points[indexPair.first] << " " << points[indexPair.second] << std::endl;
    std::cout << getDistance(points[indexPair.first], points[indexPair.second]) << std::endl;
    std::pair<int, int> indexPairIter = getShortestDistanceIter(points);
    std::cout << points[indexPairIter.first] << " " << points[indexPairIter.second] << std::endl;
    std::cout << getDistance(points[indexPairIter.first], points[indexPairIter.second]) << std::endl;
    outputFile << indexPair.first << " " << indexPair.second << " ";
    outputFile << getDistance(points[indexPair.first], points[indexPair.second]) << std::endl;
    return 0;
}

double getDistance(Point p1, Point p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

std::pair<int, int> getShortestDistance(std::vector<Point> points){
    if(points.size() < 2){
	return std::make_pair(-1, -1);
    }
    //Sort points from left to right based on x
    std::sort(points.begin(), points.end(), [](Point p1, Point p2){
	    return p1.x < p2.x;
	});
    std::vector<int> temp = std::vector<int>();
    std::pair<int, int> indexPair = getShortestRec(points, 0, points.size(), temp);
    return std::make_pair(points[indexPair.first].index, points[indexPair.second].index);
}

std::pair<int, int> getShortestRec(const std::vector<Point> &points, int start, int end, std::vector<int> &mergedPointsIndices){
    int length = end - start;
    if(length == 1){
	mergedPointsIndices.push_back(start);
	return std::make_pair(-1, -1);	
    }
    if(length == 2){
	if(points[start].y < points[end - 1].y){
	    mergedPointsIndices.push_back(start);
	    mergedPointsIndices.push_back(end - 1);
	}else{
	    mergedPointsIndices.push_back(end - 1);
	    mergedPointsIndices.push_back(start);
	}
	return std::make_pair(start, end - 1);
    }
    //Split step
    int mid = (start + end) / 2;
    std::vector<int> leftMergedIndices = std::vector<int>();
    std::vector<int> rightMergedIndices = std::vector<int>();
    std::pair<int, int> leftPair = getShortestRec(points, start, mid, leftMergedIndices);
    std::pair<int, int> rightPair = getShortestRec(points, mid, end, rightMergedIndices);
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
    mergeYSorted(points, mergedPointsIndices, leftMergedIndices, rightMergedIndices);
    std::pair<int, int> middlePair = getMiddlePair(points, mergedPointsIndices, minDistance, points[mid].y);
    if(middlePair.first != -1){;
	return middlePair;
    }else{
	return minPair;
    }
}

void mergeYSorted(const std::vector<Point> &points, std::vector<int> &mergedPointsIndices, std::vector<int> &leftMergedIndices, std::vector<int> &rightMergedIndices){
    int i = 0;
    int j = 0;    
    while(i < leftMergedIndices.size() && j < rightMergedIndices.size()){
	if(points[leftMergedIndices[i]].y < points[rightMergedIndices[j]].y){
	    mergedPointsIndices.push_back(leftMergedIndices[i]);
	    ++ i;
	}else{
	    mergedPointsIndices.push_back(rightMergedIndices[j]);
	    ++ j;	    
	}
    }
    while(i < leftMergedIndices.size()){
	mergedPointsIndices.push_back(leftMergedIndices[i]);
	++ i;
    }
    while(j < rightMergedIndices.size()){
	mergedPointsIndices.push_back(rightMergedIndices[j]);
	++ j;
    }
}

std::pair<int, int> getMiddlePair(const std::vector<Point> &points, std::vector<int> mergedPointsIndices, double minDistance, int middleY){
    std::pair<int, int> result = std::make_pair(-1, -1);
    double middleMinDistance = minDistance;
    std::vector<int>::iterator it = mergedPointsIndices.begin();
    while(it != mergedPointsIndices.end()){
	if(points[*it].x < middleY + minDistance && points[*it].x > middleY - minDistance){
	    ++ it;
	}else{
	    it = mergedPointsIndices.erase(it);
	}
    }
    if(points[0].numCoordinates == 3){
	std::vector<Point> twoDPoints = std::vector<Point>();
	std::cout << "Here" << std::endl;
	for(int i = 0; i < mergedPointsIndices.size(); ++ i){
	    Point point = Point(points[mergedPointsIndices[i]].y,
				points[mergedPointsIndices[i]].z,
				points[mergedPointsIndices[i]].x,
				2,
				points[mergedPointsIndices[i]].index);
	    twoDPoints.push_back(point);
	}
	std::cout << "Here now" << std::endl;
	std::pair<int, int> result = getShortestDistance(twoDPoints);
	return result;
    }
    if(mergedPointsIndices.size() > 0){
	for(int i = 0; i < mergedPointsIndices.size() - 1; ++ i){
	    for(int j = i + 1; j < mergedPointsIndices.size() && points[mergedPointsIndices[j]].y - points[mergedPointsIndices[i]].y < minDistance; ++ j){
		double distance = getDistance(points[mergedPointsIndices[i]], points[mergedPointsIndices[j]]);
		if(middleMinDistance > distance){
		    middleMinDistance = distance;
		    result.first = mergedPointsIndices[i];
		    result.second = mergedPointsIndices[j];
		}
	    }
	}
    }
    return result;
}

std::pair<int, int> getShortestDistanceIter(const std::vector<Point> &points){
    double minDistance = -1;
    std::pair<int, int> minPair = std::make_pair(-1, -1);
    for(int i = 0; i < points.size() - 1; ++ i){
	for(int j = i + 1; j < points.size(); ++ j){
	    double distance = getDistance(points[i], points[j]);
	    if(minDistance > distance || minDistance == -1){
		minDistance = distance;
		minPair.first = i;
		minPair.second = j;
	    }
	}
    }
    return minPair;
}
