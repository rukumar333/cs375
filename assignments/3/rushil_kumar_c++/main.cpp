#include "Graph.h"
#include <iostream>
#include <string>

int main(){
    Graph graph(11);
    graph.insertCity("Toronto");
    graph.insertCity("Buffalo");
    graph.insertCity("Rochester");
    graph.insertCity("Kingston");
    graph.insertCity("Montreal");
    graph.insertCity("Albany");
    graph.insertCity("New York City");
    graph.insertCity("Allentown");
    graph.insertCity("Scranton");
    graph.insertCity("Binghamton");
    graph.insertCity("Syracuse");
    
    graph.insertWeight("Toronto", "Kingston", 180);
    graph.insertWeight("Toronto", "Buffalo", 100);
    graph.insertWeight("Buffalo", "Rochester", 60);
    graph.insertWeight("Rochester", "Syracuse", 70);
    graph.insertWeight("Kingston", "Syracuse", 65);
    graph.insertWeight("Kingston", "Montreal", 160);
    graph.insertWeight("Syracuse", "Binghamton", 70);
    graph.insertWeight("Syracuse", "Albany", 100);
    graph.insertWeight("Montreal", "Albany", 130);
    graph.insertWeight("Albany", "New York City", 140);
    graph.insertWeight("Binghamton", "New York City", 180);
    graph.insertWeight("Binghamton", "Scranton", 60);
    graph.insertWeight("Scranton", "New York City", 100);
    graph.insertWeight("Scranton", "Allentown", 65);
    graph.insertWeight("Allentown", "New York City", 70);
    auto it = graph.cities.begin();
    while(it != graph.cities.end()){
    	std::cout << *it << " ";
    	++ it;
    }
    for(int i = 0; i < graph.weights.size(); ++ i){
    	std::cout << graph.
cities[i] << " {";
    	for(int j = 0; j < graph.weights[i].size(); ++ j){
    	    std::cout << graph.weights[i][j] << " ";
    	}
    	std::cout << "}" << std::endl;
	
    }
    return 0;
}
