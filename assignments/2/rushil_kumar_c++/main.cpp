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
std::pair<int, int> getShortestRec(const std::vector<Point> &points, int start, int end, std::vector<Point> &mergedPoints);
void mergeYSorted(std::vector<Point> &mergedPoints, std::vector<Point> &leftMerged, std::vector<Point> &rightMerged);
std::pair<int, int> getMiddlePair(std::vector<Point> mergedPoints, double minDistance, int middleY);


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
    std::vector<Point> temp = std::vector<Point>();
    return getShortestRec(points, 0, points.size(), temp);
}

std::pair<int, int> getShortestRec(const std::vector<Point> &points, int start, int end, std::vector<Point> &mergedPoints){
    int length = end - start;
    if(length == 1){
	mergedPoints.push_back(points[start]);
	return std::make_pair(-1, -1);	
    }
    if(length == 2){
	if(points[start].y < points[end - 1].y){
	    mergedPoints.push_back(points[start]);
	    mergedPoints.push_back(points[end - 1]);
	}else{
	    mergedPoints.push_back(points[end - 1]);
	    mergedPoints.push_back(points[start]);	    
	}
	return std::make_pair(start, end - 1);
    }
    //Split step
    int mid = (start + end) / 2;
    std::vector<Point> leftMerged = std::vector<Point>();
    std::vector<Point> rightMerged = std::vector<Point>();
    std::pair<int, int> leftPair = getShortestRec(points, start, mid, leftMerged);
    std::pair<int, int> rightPair = getShortestRec(points, mid, end, rightMerged);
    std::cout << "Start: " << start << std::endl;
    std::cout << "Mid: " << mid << std::endl;
    std::cout << "End: " << end << std::endl;
    std::cout << "Left: " << points[leftPair.first] << " " << points[leftPair.second] << std::endl;
    std::cout << "Right: " << points[rightPair.first] << " " << points[rightPair.second] << std::endl;
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
    mergeYSorted(mergedPoints, leftMerged, rightMerged);
    std::pair<int, int> middlePair = getMiddlePair(mergedPoints, minDistance, points[mid].y);
    std::cout << "Getting middle" << std::endl;
    if(middlePair.first != -1){
	std::cout << "Middle: " << points[middlePair.first] << " " << points[middlePair.second] << std::endl;
	return middlePair;
    }else{
	std::cout << "Not found middle" << std::endl;
	return minPair;
    }
}

void mergeYSorted(std::vector<Point> &mergedPoints, std::vector<Point> &leftMerged, std::vector<Point> &rightMerged){
    int i = 0;
    int j = 0;
    while(i < leftMerged.size() && j < rightMerged.size()){
	if(leftMerged[i].y < rightMerged[j].y){
	    mergedPoints.push_back(leftMerged[i]);
	    ++ i;
	}else{
	    mergedPoints.push_back(rightMerged[j]);
	    ++ j;	    
	}
    }
    while(i < leftMerged.size()){
	mergedPoints.push_back(leftMerged[i]);
	++ i;
    }
    while(j < rightMerged.size()){
	mergedPoints.push_back(rightMerged[j]);
	++ j;
    }
}

std::pair<int, int> getMiddlePair(std::vector<Point> mergedPoints, double minDistance, int middleY){
    std::cout << "Finding middle" << std::endl;
    std::cout << "MinDistance: "  << minDistance << std::endl;
    std::cout << "MiddleY: "  << middleY << std::endl;
    for(int i = 0; i < mergedPoints.size(); ++ i){
	std::cout << mergedPoints[i] << " ";
    }
    std::cout << std::endl;
    std::pair<int, int> result = std::make_pair(-1, -1);
    double middleMinDistance = minDistance;
    auto it = mergedPoints.begin();
    while(it != mergedPoints.end()){
	if(it->x < middleY + minDistance && it->x > middleY - minDistance){
	    ++ it;
	}else{
	    it = mergedPoints.erase(it);
	}
    }
    for(int i = 0; i < mergedPoints.size(); ++ i){
	std::cout << mergedPoints[i] << " ";
    }
    std::cout << std::endl;
    if(mergedPoints.size() > 0){
	for(int i = 0; i < mergedPoints.size() - 1; ++ i){
	    for(int j = i + 1; j < mergedPoints.size() && mergedPoints[j].y - mergedPoints[i].y < minDistance; ++ j){
		double distance = getDistance(mergedPoints[i], mergedPoints[j]);
		if(middleMinDistance > distance){
		    middleMinDistance = distance;
		    result.first = i;
		    result.second = j;
		}
	    }
	}
    }
    return result;
}
