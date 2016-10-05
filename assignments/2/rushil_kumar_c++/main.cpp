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
std::pair<int, int> getShortestDistance(const std::vector<Point> &points);
std::pair<int, int> getShortestRec(const std::vector<Point> &points, int start, int end, std::vector<int> &mergedPointsIndices);
void mergeYSorted(const std::vector<Point> &points, std::vector<int> &mergedPointsIndices, std::vector<int> &leftMergedIndices, std::vector<int> &rightMergedIndices);
std::pair<int, int> getMiddlePair(const std::vector<Point> &points, std::vector<int> mergedPointsIndices, double minDistance, int middleY);


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
    std::pair<int, int> indexPair = getShortestDistance(points);
    std::cout << points[indexPair.first] << " " << points[indexPair.second] << std::endl;
}

double getDistance(Point p1, Point p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

std::pair<int, int> getShortestDistance(const std::vector<Point> &points){
    std::vector<int> temp = std::vector<int>();
    return getShortestRec(points, 0, points.size(), temp);
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
    auto it = mergedPointsIndices.begin();
    while(it != mergedPointsIndices.end()){
	if(points[*it].x < middleY + minDistance && points[*it].x > middleY - minDistance){
	    ++ it;
	}else{
	    it = mergedPointsIndices.erase(it);
	}
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
