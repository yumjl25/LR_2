CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

$(shell mkdir -p bin)

all: task1 task2 task3 task4 task5 task6.1 task6.2 task7

task1: src/stack.cpp tasks/rpn.cpp
	$(CXX) $(CXXFLAGS) $^ -o bin/task1

task2: src/hash.cpp tasks/set.cpp
	$(CXX) $(CXXFLAGS) $^ -o bin/task2

task3: src/hash.cpp tasks/turtles.cpp
	$(CXX) $(CXXFLAGS) $^ -o bin/task3

task4: src/array.cpp tasks/histogram.cpp
	$(CXX) $(CXXFLAGS) $^ -o bin/task4

task5: src/tree.cpp tasks/huffman.cpp
	$(CXX) $(CXXFLAGS) $^ -o bin/task5

task6.1: src/cuckoo.cpp src/hash.cpp tasks/benchmark.cpp
	$(CXX) $(CXXFLAGS) $^ -o bin/task6.1

task6.2: src/cuckoo.cpp tasks/isomorphic.cpp
	$(CXX) $(CXXFLAGS) $^ -o bin/task6.2

task7: src/list.cpp src/hash.cpp tasks/lfu.cpp
	$(CXX) $(CXXFLAGS) $^ -o bin/task7

clean:
	rm -f bin/*