CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
 
TARGET = topsort_dfs
 
all: $(TARGET)
 
$(TARGET): topsort_dfs.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) topsort_dfs.cpp
 
clean:
	rm -f $(TARGET)