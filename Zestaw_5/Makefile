CXX = g++
CXXFLAGS = -std=c++17 -Wall
 
all: bfs
 
bfs: main.cpp bfs.hpp graph.hpp
	$(CXX) $(CXXFLAGS) -o bfs main.cpp
 
clean:
	rm -f bfs