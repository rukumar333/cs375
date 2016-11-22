#include "DisjointSet.h"

DisjointSet::DisjointSet(int count) : sets(0, count){
    for(int i = 0; i < sets.size(); ++ i){
	sets[i] = i;
    }
}

int DisjointSet::find(int photo){
    
}

void merge(int firstPhoto, int secondPhoto){
    int firstRep = find(firstPhoto);
    int secondRep = find(secondPhoto);
    
}
