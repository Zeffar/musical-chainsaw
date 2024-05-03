CXX = g++
CXXFLAGS = -std=c++23 -O2

TARGET = benchmark
SRC = benchmark.cpp

$(TARGET): $(SRC) 
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
