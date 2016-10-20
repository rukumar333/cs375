#include "Graph.h"

Graph::Graph() : weights(), cities(){
    // cities = std::set<std::string>();
    // weights = std::vector<std::vector<int> >();
}

Graph::Graph(int numCities) : weights(numCities, std::vector<int>(numCities, -1)), cities(){
    
}

void Graph::insertCity(std::string city){
    cities.insert(city);
}

void Graph::insertWeights(std::string city, std::vector<int> weights){
    // int index = cities.find(city) - cities.begin();    
    std::set<std::string>::iterator it = cities.find(city);
    int index = std::distance(it, cities.begin());
    this->weights[index] = weights;
}

void Graph::insertWeight(std::string cityA, std::string cityB, int weight){
    int indexA = std::distance(cities.find(cityA), cities.end());
    int indexB = std::distance(cities.find(cityB), cities.end());
    weights[indexA][indexB] = weight;
    weights[indexB][indexA] = weight;    
}


