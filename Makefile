all:
	g++ -Wall -g -std=c++17 Graph.cpp GraphTests.cpp -o graph-tests
	g++ -Wall -g -std=c++17 Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp -o bpq-tests