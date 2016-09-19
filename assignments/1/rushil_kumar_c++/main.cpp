#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>

class Node{    
public:
    int firstIndex;
    int secondIndex;
    int difference;
    Node(int firstIndex, int secondIndex, int difference);
};

Node::Node(int firstIndex, int secondIndex, int difference){
    this->firstIndex = firstIndex;
    this->secondIndex = secondIndex;
    this->difference = difference;
}

void printDifferences(std::vector<int> numbers, char * outputFileName);

int main(int argc, char * args[]){
    if(argc < 2){
	std::cout << "Not enough arguments provided." << std::endl;
	return 0;
    }
    std::ifstream file(args[1]);
    std::string input;
    std::vector<int> numbers;
    while(std::getline(file, input)){
	numbers.push_back(std::stoi(input));
    }
    printDifferences(numbers, args[2]);
    return 0;
}

void printDifferences(std::vector<int> numbers, char * outputFileName){
    std::unordered_multimap<int, Node> hashmap = std::unordered_multimap<int, Node>();
    for(int i = 0; i < numbers.size() - 1; ++ i){
	for(int k = i + 1; k < numbers.size(); ++ k){
	    int difference = abs(numbers[i] - numbers[k]);
	    int bigger, smaller;
	    if(numbers[i] < numbers[k]){
		bigger = k;
		smaller = i;
	    }else{
		bigger = i;
		smaller = k;
	    }
	    std::pair<int, Node> pairData(difference, Node(bigger, smaller, difference));
	    hashmap.insert(pairData);
	}
    }
    std::ofstream file(outputFileName);
    for(int i = 0; i < numbers.size(); ++ i){
	auto range = hashmap.equal_range(abs(numbers[i]));
	auto it = range.first;
	while(it != range.second){
	    if(i != it->second.firstIndex && i != it->second.secondIndex){
		file << numbers[i] << " " << numbers[it->second.firstIndex] << " " << numbers[it->second.secondIndex] << std::endl;
	    }
	    ++ it;
	}
    }
}
