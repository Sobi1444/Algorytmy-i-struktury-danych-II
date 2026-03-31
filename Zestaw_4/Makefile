CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: main

main: main.cpp graph.hpp basegraph.hpp edge.hpp iterator.hpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	rm -f main