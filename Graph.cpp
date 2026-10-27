// Author: Teague Wright
// Used Claude (Anthropic) to generate the initial empty method stubs and to review my code.

#include "Graph.h"
#include <stdexcept>

using namespace std;

Graph::Graph() {
    // TODO:
}

Graph::Graph(const Graph &other) {
    // TODO: (ungraded)
}

Graph::~Graph() {
    // TODO: delete every heap GraphEdge
}

void Graph::AddNode(nodekey_t key) {
    // TODO:
}

const GraphEdge* Graph::AddEdge(nodekey_t fromNodeKey, nodekey_t toNodeKey, unsigned int weight) {
    // TODO:
    return nullptr;
}

bool Graph::IsPresent(nodekey_t key) const {
    // TODO:
    return false;
}

string Graph::NodesToString() const {
    // TODO:
    return "";
}

string Graph::EdgesToString() const {
    // TODO:
    return "";
}

set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t nodeKey) const {
    // TODO:
    return {};
}

set<nodekey_t> Graph::GetNodes() const {
    // TODO:
    return {};
}

size_t Graph::Size() const {
    // TODO:
    return 0;
}

size_t Graph::Order() const {
    // TODO:
    return 0;
}
