FLAGS = -g -std=c++11

all: main.o DisjointSet.o
	g++ $(FLAGS) main.o DisjointSet.o -o main.exe

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

DisjointSet.o: DisjointSet.cpp DisjointSet.h
	g++ $(FLAGS) -c DisjointSet.cpp

clean:
	rm main.exe *.o
