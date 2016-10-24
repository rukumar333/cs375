#include "Graph.h"
#include <iostream>
#include <string>

std::vector<std::vector<std::vector<int> > > lengthLCS(std::string str1, std::string str2, std::string str3);
std::string LCS(std::string str1, std::string str2, std::string str3);

int main(){
    std::string str1 = "6541254939322816220209974565477289648317";
    std::string str2 = "3142522751761601737419090933147067701840";
    std::string str3 = "28070305612903542595135701601 62463275171";
    std::cout << "LCS of strings str1, str2, str3" << std::endl;
    std::cout << "str1: " << str1 << std::endl;
    std::cout << "str2: " << str2 << std::endl;
    std::cout << "str3: " << str3 << std::endl;
    std::string result = LCS(str1, str2, str3);
    std::cout << "Length LCS: " << result.size() << std::endl;
    std::cout << "LCS: " << result << std::endl;
    std::cout << std::endl;
    Graph graph(11);
    //Insert cities
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
    //Sort cities    
    std::sort(graph.cities.begin(), graph.cities.end());

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
    std::cout << "Shortest path from New York City to Toronto" << std::endl;
    graph.printShortestPath("New York City", "Toronto");
    return 0;
}


/*
  Returns the 3D table for calculating the length of the LCS
 */
std::vector<std::vector<std::vector<int> > > lengthLCS(std::string str1, std::string str2, std::string str3){
    // Initialize 3D table
    std::vector<std::vector<std::vector<int> > > table(str1.size() + 1, std::vector<std::vector<int> >(str2.size() + 1, std::vector<int>(str3.size() + 1, 0)));
    for(int i = 1; i < table.size(); ++ i){
	for(int j = 1; j < table[i].size(); ++ j){
	    for(int k = 1; k < table[i][j].size(); ++ k){
		// If characters at index are same, increase length of LCS by one.
		if(str1[i - 1] == str2[j - 1] && str2[j - 1] == str3[k - 1]){
		    table[i][j][k] = table[i - 1][j - 1][k - 1] + 1;
		}else{
		    //If characters are not the same, get max between not including the char from str1,
		    //str2, and str3.
		    int length1 = table[i - 1][j][k];
		    int length2 = table[i][j - 1][k];
		    int length3 = table[i][j][k - 1];
		    table[i][j][k] = std::max({length1, length2, length3});
		}
	    }
	}
    }
    return table;
}

std::string LCS(std::string str1, std::string str2, std::string str3){
    std::vector<std::vector<std::vector<int> > > table = lengthLCS(str1, str2, str3);
    std::string result = "";
    // std::cout << "Length: " << table[str1.size()][str2.size()][str3.size()] << std::endl;
    int i = str1.size();
    int j = str2.size();
    int k = str3.size();
    int currentLength = 0;
    //Traverse 3D table by checking when the characters are the same
    while(i > 0 && j > 0 && k > 0){
	currentLength = table[i][j][k];
	if(str1[i - 1] == str2[j - 1] && str2[j - 1] == str3[k - 1]){
	    result = str1[i - 1] + result;
	    i = i - 1;
	    j = j - 1;
	    k = k - 1;
	}else{
	    if(table[i - 1][j][k] == currentLength){
	    	i = i - 1;
	    }else{
	    	if(table[i][j - 1][k] == currentLength){
	    	    j = j - 1;
	    	}else{
	    	    if(table[i][j][k - 1] == currentLength){
	    		k = k - 1;
	    	    }
	    	}
	    }
	}
    }
    return result;
}
