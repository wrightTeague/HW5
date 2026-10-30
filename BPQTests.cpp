// Author: Teague Wright
// Tests provided by the professor. Claude (Anthropic) wrote ToStringTest and HeapOrderTest.

#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <cassert>
#include <iostream>

using namespace std;

void ContainsTest() {
	cout << "Testing Contains Helper Method..." << endl;
	
	Graph g = Graph();
	BetterPriorityQueue q;
	
	g.AddNode(1);
	g.AddNode(2);
	g.AddNode(3);
	g.AddNode(4);
	g.AddNode(5);
	g.AddNode(6);
	set<nodekey_t> nodes = g.GetNodes();
	for(nodekey_t n : nodes){
		BPQNode cur;
		cur.gnode = n;
		//cout << "inserting cur.pri: " << cur.pri << "  node: " << cur.node->key << endl;
		q.push(cur);
		//cout << "size: " << q.size() << endl;
	}
	
	
	// 1st test
	BPQNode positive;
	positive.gnode = 2;
	assert(q.Contains(positive) == true);
	
	// 2nd test
	BPQNode negative;
	assert(q.Contains(negative) == false);
	
	// 3rd test (just to ensure it still works after 2nd test finishes)
	assert(q.Contains(positive) == true);
	
	
	cout << "PASSED!" << endl;
}



void UpdateTest() {
	cout << "Testing Update Helper Method..." << endl;
	
	Graph g = Graph();
	BetterPriorityQueue q;
	
	g.AddNode(1);
	g.AddNode(2);
	g.AddNode(3);
	g.AddNode(4);
	g.AddNode(5);
	g.AddNode(6);
	set<nodekey_t> nodes = g.GetNodes();
	size_t i = 0;
	for(nodekey_t n : nodes){
		BPQNode cur;
		cur.pri = i;
		cur.gnode = n;
		//cout << "inserting cur.pri: " << cur.pri << "  node: " << cur.node->key << endl;
		q.push(cur);
		//cout << "size: " << q.size() << endl;
		i++;
	}
	

	//cout << "q before: " << queue_to_string(q) << endl;

	// Test 1: update a node with pri 0 (normal case)
	BPQNode positive;
	positive.gnode = 6;
	positive.pri = 0;
	cout << "q before: " << q.ToString() << endl;
	assert(q.Update(positive) == true);
	cout << "q after: " << q.ToString() << endl;



	// some students might have a slightly different order
	// please ensure the output is a valid priorityqueue as 
	// implemented by a binary heap.  Any valid order is fine!
	string soln1 = "[(6, pri: 0), (1, pri: 0), (2, pri: 1), (3, pri: 2), (4, pri: 3), (5, pri: 4)]";
	string soln2 = "[(1, pri: 0), (2, pri: 1), (6, pri: 0), (4, pri: 3), (5, pri: 4), (3, pri: 2)]";
	string soln3 = "[(1, pri: 0), (6, pri: 0), (2, pri: 1), (3, pri: 2), (4, pri: 3), (5, pri: 4)]";

	
	// Test 2: attempt to update with an empty / undefined input
	BPQNode negative;
	assert(q.Update(negative) == false);
	cout << "q after test 2: " << q.ToString() << endl;
	assert(q.ToString() == soln1 || q.ToString() == soln2 || q.ToString() == soln3);
	

	// Test 3: update a node with a larger priority
	// It must behave this way (ignoring larger priorities)
	// for compatibility with Dijkstra's algorithm
	BPQNode negative2;
	negative2.gnode = 5;
	negative2.pri = 80;
	assert(q.Update(negative2) == false);
	cout << "q after test 3: " << q.ToString() << endl;
	assert(q.ToString() == soln1 || q.ToString() == soln2 || q.ToString() == soln3);	
	
	cout << "PASSED!" << endl;
}

void ToStringTest() {
	cout << "Testing ToString..." << endl;
	
	BetterPriorityQueue q;
	assert(q.ToString() == "[]");
	
	BPQNode n;
	n.gnode = 6;
	n.pri = 0;
	assert(BetterPriorityQueue::BPQNodeToString(n) == "(6, pri: 0)");
	
	q.push(n);
	assert(q.ToString() == "[(6, pri: 0)]");
	
	cout << "PASSED!" << endl;
}

void HeapOrderTest() {
	cout << "Testing heap order after Update..." << endl;
	
	BetterPriorityQueue q;
	for (nodekey_t k = 1; k <= 7; k++) {
		BPQNode n;
		n.gnode = k;
		n.pri = k * 10;
		q.push(n);
	}
	
	// node 7 has to climb two levels to become the new root
	BPQNode lower;
	lower.gnode = 7;
	lower.pri = 5;
	assert(q.Update(lower) == true);
	assert(q.top().gnode == 7);
	
	// an equal priority isn't a change
	assert(q.Update(lower) == false);
	
	// lowering node 5 without passing node 1 leaves the same root
	lower.gnode = 5;
	lower.pri = 15;
	assert(q.Update(lower) == true);
	assert(q.top().gnode == 7);
	
	// a valid heap has to give everything back in priority order
	nodekey_t expected[] = {7, 1, 5, 2, 3, 4, 6};
	for (nodekey_t k : expected) {
		assert(q.top().gnode == k);
		q.pop();
	}
	assert(q.empty());
	
	// popped nodes are gone, so they can't be updated
	assert(q.Contains(lower) == false);
	assert(q.Update(lower) == false);
	
	cout << "PASSED!" << endl;
}

int main(){
	
	ContainsTest();
	UpdateTest();
	ToStringTest();
	HeapOrderTest();
	
	cout << "ALL TESTS PASSED!!" << endl;
	
	return 0;
	
}
