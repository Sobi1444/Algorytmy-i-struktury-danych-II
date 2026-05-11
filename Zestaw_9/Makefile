CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = floyd_warshall
SRC = main.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean run
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)