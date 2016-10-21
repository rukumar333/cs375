#include "Graph.h"

Graph::Graph() : weights(), cities(){

}

Graph::Graph(int numCities) : weights(numCities, std::vector<int>(numCities, -1)),
			      intermediateNodes(numCities, std::vector<int>(numCities, -1)),
			      cities(){
    for(int i = 0; i < numCities; ++ i){
	weights[i][i] = 0;
    }
}

void Graph::insertCity(std::string city){
    cities.push_back(city);
}

void Graph::insertWeight(std::string cityA, std::string cityB, int weight){
    auto itA = std::find(cities.begin(), cities.end(), cityA);
    auto itB = std::find(cities.begin(), cities.end(), cityB);
    int indexA = itA - cities.begin();
    int indexB = itB - cities.begin();
    weights[indexA][indexB] = weight;
    weights[indexB][indexA] = weight;    
}

std::vector<std::vector <int> > Graph::floydsAlgorithm(){
    std::vector<std::vector<int > > distances = weights;
    //k -> intermediate node
    for(int k = 0; k < distances.size(); ++ k){
	for(int i = 0; i < distances.size(); ++ i){
	    for(int j = 0; j < distances.size(); ++ j){
		if(distances[i][k] != -1 && 
		   distances[k][j] != -1 && 
		   (distances[i][j] > distances[i][k] + distances[k][j] ||
		    distances[i][j] == -1)){
		    distances[i][j] = distances[i][k] + distances[k][j];
		    intermediateNodes[i][j] = k;
		}
	    }
	}
    }
    return distances;
}

void Graph::printShortestPath(std::string cityStart, std::string cityEnd){
    std::vector<std::vector<int > > distances = floydsAlgorithm();
    auto itStart = std::find(cities.begin(), cities.end(), cityStart);
    auto itEnd = std::find(cities.begin(), cities.end(), cityEnd);
    int indexStart = itStart - cities.begin();
    int indexEnd = itEnd - cities.begin();
    if(distances[indexStart][indexEnd] == -1){
	std::cout << "No path found between " << cityStart << " and " << cityEnd << std::endl;
    }else{
	std::cout << "Distance: " << distances[indexStart][indexEnd] << " miles" << std::endl;
	std::cout << cityStart << " -> ";
	printShortestPath(indexStart, indexEnd);	
	std::cout << cityEnd << std::endl;
    }
}

void Graph::printShortestPath(int startIndex, int endIndex){
    int intermediateIndex = intermediateNodes[startIndex][endIndex];
    if(intermediateNodes[startIndex][endIndex] != -1){
	printShortestPath(startIndex, intermediateIndex);
	std::cout << cities[intermediateIndex] << " -> ";
	printShortestPath(intermediateIndex, endIndex);
    }
}




