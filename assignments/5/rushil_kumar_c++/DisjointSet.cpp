#include "DisjointSet.h"

DisjointSet::DisjointSet(int count, std::vector<Edge> edges) : sets(count, 0), heights(count, 0), edges(edges), numSets(count){
    
    for(int i = 0; i < sets.size(); ++ i){
	sets[i] = i;
    }
}

int DisjointSet::find(int photo){
    int root = photo;
    while(root != sets[root]){
	root = sets[root];
    }
    int node = photo;
    while(node != root){
	int parent = sets[node];
	sets[node] = root;
	node = parent;
    }
    return root;
}

void DisjointSet::merge(int firstPhoto, int secondPhoto){
    int firstRep = find(firstPhoto);
    int secondRep = find(secondPhoto);
    if(firstRep != secondRep){
	-- numSets;
	if(heights[firstRep] == heights[secondRep]){
	    ++ heights[firstRep];
	    sets[secondRep] = firstRep;
	}else{
	    if(heights[firstRep] > heights[secondRep]){
		sets[secondRep] = firstRep;
	    }else{
		sets[firstRep] = secondRep;	    
	    }
	}
    }
}

void DisjointSet::kruksallsAlgorithm(){
    std::sort(this->edges.begin(), this->edges.end(), [](Edge a, Edge b){
	    return b.weight < a.weight;
	});
    for(Edge &e : this->edges){
	merge(e.first, e.second);
	if(numSets == 3){
	    printSets();
	    return;
	}
    }
}


void DisjointSet::printSets(){
    for(int i = 0; i < 20; ++ i){
	find(i);
    }
    std::unordered_map<int, std::vector<int> > hashmap = std::unordered_map<int, std::vector<int> >();
    for(int i = 0; i < sets.size(); ++ i){
	if(hashmap.find(sets[i]) == hashmap.end()){
	    hashmap[sets[i]] = std::vector<int>();	    
	}
	hashmap[sets[i]].push_back(i + 1);
    }
    auto it = hashmap.begin();
    std::cout << "Sets:" << std::endl;
    while(it != hashmap.end()){
	for(int i = 0; i < it->second.size(); ++ i){
	    std::cout << it->second[i];
	    if(i < it->second.size() - 1){
		std::cout << ", ";
	    }
	}
	std::cout << std::endl;
	++ it;
    }
}
