CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
 
TARGET = connected
 
$(TARGET): main.cpp connected.hpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp
 
clean:
	rm -f $(TARGET)
