FLAGS = -g -std=c++11

all: main.o Graph.o
	g++ $(FLAGS) main.o Graph.o -o main.exe
main.o: main.cpp
	g++ $(FLAGS) -c main.cpp
Graph.o: Graph.cpp Graph.h
	g++ $(FLAGS) -c Graph.cpp
clean:
	rm *.o *.exe
