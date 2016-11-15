FLAGS = -std=c++17 -g

all: main.o
	g++ $(FLAGS) main.o Graph.o -o main.exe

main.o: main.cpp Graph.o
	g++ $(FLAGS) -c main.cpp

Graph.o: Graph.cpp
	g++ $(FLAGS) -c Graph.cpp

clean:
	rm *.o *.exe
