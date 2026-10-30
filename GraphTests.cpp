// Author: Teague Wright
// Tests provided by the professor. Claude (Anthropic) wrote the additional tests at the "more tests" spots.

#include "Graph.h"
#include <iostream>
#include <cassert>

using namespace std;



void TestAddNode(){
	cout << "Testing AddNode..." << endl;
	Graph g = Graph();


	g.AddNode(15);
	//cout << "nodes: " << g.NodesToString() << endl;
	assert(g.NodesToString() == "[(15)]");


	g.AddNode(12);
	//cout << "nodes: " << g.NodesToString() << endl;
	assert(g.NodesToString() == "[(15), (12)]");

	
	try
	{
		g.AddNode(12);
		assert(false);
	}
	catch( const invalid_argument& e ) { }

	
	cout << "PASSED!" << endl << endl;
}


void TestAddEdge(){
	cout << "Testing AddEdge..." << endl;
	Graph g = Graph();

	g.AddNode(15);
	g.AddNode(12);
	g.AddNode(9);
	// cout << "nodes: " << g.NodesToString() << endl;
	assert(g.NodesToString() == "[(15), (12), (9)]");

	
	const GraphEdge *ge1 = g.AddEdge(15, 9, 2);
	assert(g.NodesToString() == "[(15), (12), (9)]");
	//cout << "edges:" <<  g.EdgesToString() << endl;
	assert(g.EdgesToString() == "[((15)->(9) w:2)]");
	assert(ge1->from == 15);
	assert(ge1->to == 9);
	assert(ge1->weight == 2);
	
	const GraphEdge *ge2 = g.AddEdge(9, 12); // this makes the weight 0, since default value for weight is 0
	assert(g.NodesToString() == "[(15), (12), (9)]");
	//cout << "edges:" <<  g.EdgesToString() << endl;
	assert(g.EdgesToString() == "[((15)->(9) w:2), ((9)->(12) w:0)]");
	assert(ge2->from == 9);
	assert(ge2->to == 12);
	assert(ge2->weight == 0);
	
	try
	{
		const GraphEdge *ge3 = g.AddEdge(20, 12);
		cout << "ge3: (" + to_string(ge3->from) + "->" + to_string(ge3->to) + "  w: " + to_string(ge3->weight) + ")" << endl;
		assert(false);
	} catch (const invalid_argument& e) {}


	try
	{
		const GraphEdge *ge3 = g.AddEdge(15, 9, 7);
		// edge already exists!
		cout << "ge3: (" + to_string(ge3->from) + "->" + to_string(ge3->to) + "  w: " + to_string(ge3->weight) + ")" << endl;
		assert(false);
	} catch (const invalid_argument& e) {}


	// a reverse edge is a different edge, since the graph is directed
	g.AddEdge(9, 15, 4);
	assert(g.Size() == 3);

	try
	{
		g.AddEdge(15, 20);
		assert(false);
	} catch (const invalid_argument& e) {}

	Graph empty = Graph();
	assert(empty.NodesToString() == "[]");
	assert(empty.EdgesToString() == "[]");
	
	cout << "PASSED!" << endl << endl;
}


void TestIsPresentSizeAndOrder() {
	cout << "Testing IsPresent, Size, and Order..." << endl;
	
	Graph g = Graph();
	g.AddNode(1);
	g.AddNode(2);
	g.AddEdge(1, 2, 5);
	assert(g.Size() == 1);
	assert(g.Order() == 2);
	assert(g.IsPresent(1) == true);
	assert(g.IsPresent(3) == false);

	Graph g2 = Graph();
	assert(g2.Size() == 0);
	assert(g2.Order() == 0);
	assert(g2.IsPresent(17) == false);


	cout << "PASSED!" << endl << endl;
}



void TestGetOutwardEdgesFrom(){
	cout << "Testing GetOutwardEdgesFrom..." << endl;
	Graph g = Graph();
	g.AddNode(17);
	g.AddNode(18);
	g.AddNode(22);
	g.AddNode(34);

	const GraphEdge* ge1 = g.AddEdge(17, 18, 3);
	g.AddEdge(22, 18); // weight will be 0 of course
	const GraphEdge* ge3 = g.AddEdge(17, 34, 8);
	g.AddEdge(22, 17, 6); // note, 22 is not a neighbor of 17, but 17 is a neighbor of 22
	
	set<const GraphEdge*> soln;
	soln.insert(ge3);
	soln.insert(ge1);
	
	set<const GraphEdge*> result = g.GetOutwardEdgesFrom(17);
	assert(result.size() == soln.size());
	assert(result == soln);


	assert(g.GetOutwardEdgesFrom(18).empty());

	try
	{
		g.GetOutwardEdgesFrom(99);
		assert(false);
	} catch (const invalid_argument& e) {}
	
	
	cout << "PASSED!" << endl << endl;
}


void TestGetNodes(){
	cout << "Testing GetNodes..." << endl;
		
	Graph g = Graph();
	g.AddNode(51);
	g.AddNode(24);
	g.AddNode(73);

	
	set<nodekey_t> nodes = g.GetNodes();
	set<nodekey_t> soln = {24, 73, 51};
	assert(nodes.size() == soln.size());
	assert(nodes == soln);


	g = Graph();
	nodes = g.GetNodes();
	soln.clear();
	assert(nodes.size() == soln.size());
	assert(nodes == soln);
		
	cout << "PASSED!" << endl << endl;
}




void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;
	Graph g = Graph();
	g.AddNode(1);
	g.AddNode(2);
	g.AddEdge(1, 2, 5);

	Graph copy = Graph(g);
	assert(copy.NodesToString() == g.NodesToString());
	assert(copy.EdgesToString() == g.EdgesToString());
	assert(copy.Size() == 1);

	// the copy owns separate edges, so changing it leaves the original alone
	copy.AddEdge(2, 1, 3);
	assert(copy.Size() == 2);
	assert(g.Size() == 1);
	assert(*g.GetOutwardEdgesFrom(1).begin() != *copy.GetOutwardEdgesFrom(1).begin());

	cout << "PASSED!" << endl << endl;
}


void TestDestructor(){
	cout << "Testing Destructor..." << endl;
	Graph *g = new Graph();

	g->AddNode(3);
	g->AddNode(5);
	g->AddEdge(3, 5, 15);
	delete g;
	
	
	Graph *g2 = new Graph();
	g2->AddNode(12);
	g2->AddNode(11);
	delete g2;


	Graph *g3 = new Graph();
	delete g3;
	
	
	Graph g4 = Graph(); // deconstructed automatically when this funciton ends
	
	cout << "NO ERRORS.  Use valgrind to check!" << endl << endl;
}



int main(){
	
	TestAddNode();
	TestAddEdge();
	TestIsPresentSizeAndOrder();
	TestGetOutwardEdgesFrom();
	TestGetNodes();
	TestCopyConstructor();
	TestDestructor();

	
	cout << "ALL TESTS PASSED!" << endl;
	return 0;
}
