all: main

main: main.cpp
	g++ -g -std=c++11 -o submission main.cpp

test: test.cpp
	g++ -g -std=c++11 -o test test.cpp
	./test > input.txt

clean:
	rm submission test
