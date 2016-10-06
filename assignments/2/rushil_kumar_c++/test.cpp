#include <iostream>
#include <string>
#include <cmath>
#include <time.h>
#include <cmath>

void first();
void second();
void third();
void fourth();

int main(int argc, char *argv[]){    
    // first();
    // second();
    // third();
    fourth();
}

void first(){
    int n = 10000;
    for(int i = 0; i < n; ++ i){
	std::cout << n - i << " " << n - i << std::endl;
    }
}

void second(){
    int n = 10000;
    for(int i = 0; i < n; ++ i){
	std::cout << i * i << " " << i * i << std::endl;
    }    
}

void third(){
    int x = 1;
    while(x <= 19999){
	int y = int(sqrt(pow(9999, 2) - pow(x - 10000, 2)));
	std::cout << x << " " << y << std::endl;
	x = x + 2;
    }
    x = 0;
    while(x > -20000){
	int y = int(sqrt(pow(10000, 2) - pow(x + 10000, 2)));
	std::cout << x << " " << y << std::endl;
	x = x - 2;	
    }
}

void fourth(){
    int length = 100;
    srand(time(NULL));
    for(int i = 0; i < length; ++ i){
	std::cout << rand() % 20000 - 10000 << " " << rand() % 20000 - 10000 << " " << rand() % 20000 - 10000 << std::endl;
    }
}
