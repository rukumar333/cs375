#include "Graph.h"

// int INT_MAX = std::numeric_limits<int>::max();

Graph::Graph() : weights(), cities(){
    // cities = std::set<std::string>();
    // weights = std::vector<std::vector<int> >();
}

Graph::Graph(int numCities) : weights(numCities, std::vector<int>(numCities, -1)), cities(){
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

std::vector<std::vector <int> > floydsAlgorithm(){
    std::vector<std::vector<int > > distances() = weights;
    std::vector<std::vector<int > > intermediateNodes(distances.size(), std::vector<int>(distances.size(), -1));
    //k -> intermediate node
    for(int k = 0; k < distances.size(); ++ k){
	for(int i = 0; i < distances.size(); ++ i){
	    for(int j = 0; j < distances.size(); ++ j){
		if(distances[i][j] > distances[i][k] + distances[k][j]){
		    distances[i][j] = distances[i][k] + distances[k][j];
		    intermediateNodes[i][j] = k;
		}
	    }
	}
    }
    return distances;
}




