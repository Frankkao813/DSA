CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = bst.out
SOURCE = bst.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
