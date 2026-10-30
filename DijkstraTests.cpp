// Author: Teague Wright
// Tests provided by the professor. Claude (Anthropic) wrote SpecGraphTest and EdgeCaseTest.

#include "Graph.h"
#include "BetterPriorityQueue.h"
#include "Dijkstra.h"

#include <iostream>
#include <cassert>

using namespace std;


int DijkstraTest(){
	cout << "Testing Dijkstra Algorithm..." << endl;
	
	// Test 1: graph from assignment
	Graph *g = new Graph();
	
	g->AddNode(1);
	g->AddNode(2);
	g->AddNode(3);
	
	g->AddEdge(1, 2, 7);
	g->AddEdge(2, 1, 7);
	g->AddEdge(1, 3, 9);
	g->AddEdge(3, 1, 9);

	
	cout <<  "---Graph---" << endl;
	cout << "\tnodes: " << g->NodesToString() << endl;
	cout << "\tedges: " << g->EdgesToString() << endl;
	cout << "---Graph---" << endl << endl;

	nodekey_t start = 1;
	nodekey_t end = 3;

	cout << "start: " << to_string(start) << "  goal: " << to_string(end) << endl;
	
	int ans = dijkstra(start, end, g);
	cout << "Output from Dijkstra(" << to_string(start) << ", " << to_string(end) << ") => " << ans << endl;
	assert(ans == 9);

	delete g;
	
	cout << "DONE with basic testing of Dijkstra algorithm" << endl;
	
	return ans;
}



void SpecGraphTest(){
	cout << "Testing the graph pictured in the spec..." << endl;
	
	Graph g = Graph();
	for (nodekey_t k = 1; k <= 6; k++) {
		g.AddNode(k);
	}
	
	// the pictured edges go both ways
	nodekey_t pairs[][2] = {{1, 2}, {1, 3}, {1, 6}, {2, 3}, {2, 4}, {3, 4}, {3, 6}, {4, 5}, {5, 6}};
	unsigned int weights[] = {7, 9, 14, 10, 15, 11, 2, 6, 9};
	for (int i = 0; i < 9; i++) {
		g.AddEdge(pairs[i][0], pairs[i][1], weights[i]);
		g.AddEdge(pairs[i][1], pairs[i][0], weights[i]);
	}
	
	assert(dijkstra(1, 5, &g) == 20);
	assert(dijkstra(5, 1, &g) == 20);
	assert(dijkstra(1, 4, &g) == 20);
	assert(dijkstra(1, 1, &g) == 0);
	
	cout << "PASSED!" << endl;
}

void EdgeCaseTest(){
	cout << "Testing Dijkstra edge cases..." << endl;
	
	// the cheaper path has more hops than the direct edge
	Graph indirect = Graph();
	indirect.AddNode(1);
	indirect.AddNode(2);
	indirect.AddNode(3);
	indirect.AddEdge(1, 2, 4);
	indirect.AddEdge(1, 3, 1);
	indirect.AddEdge(3, 2, 2);
	assert(dijkstra(1, 2, &indirect) == 3);
	
	// edges are one-way
	assert(dijkstra(2, 1, &indirect) == INT_MAX);
	
	// rubric question 4: three nodes with no edges
	Graph disconnected = Graph();
	disconnected.AddNode(1);
	disconnected.AddNode(2);
	disconnected.AddNode(3);
	assert(dijkstra(1, 2, &disconnected) == INT_MAX);
	
	// an edge between two unreachable nodes must not overflow into a negative distance
	Graph unreachable = Graph();
	unreachable.AddNode(1);
	unreachable.AddNode(2);
	unreachable.AddNode(3);
	unreachable.AddEdge(2, 3, 5);
	assert(dijkstra(1, 3, &unreachable) == INT_MAX);
	
	// a zero weight edge is still a real path
	Graph zero = Graph();
	zero.AddNode(1);
	zero.AddNode(2);
	zero.AddEdge(1, 2);
	assert(dijkstra(1, 2, &zero) == 0);
	
	// end isn't in the graph
	assert(dijkstra(1, 99, &zero) == INT_MAX);
	
	cout << "PASSED!" << endl;
}

int main(){
	
	DijkstraTest(); // this one by itself tests the graph on the assignment
	SpecGraphTest();
	EdgeCaseTest();
	cout << endl;
	cout << "ALL TESTS PASSED!" << endl;

	return 0;
}
