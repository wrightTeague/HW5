// Author: Teague Wright
// Used Claude (Anthropic) to generate the initial empty method stubs and to review my code. Claude wrote the copy constructor.

#include "Graph.h"
#include <stdexcept>

using namespace std;

Graph::Graph() {
}

// Goes through AddEdge so the copy gets its own heap edges; sharing them would make both destructors delete them.
Graph::Graph(const Graph &other) {
    for (nodekey_t k : other.keys) {
        AddNode(k);
    }
    for (const vector<GraphEdge*> &row : other.edges) {
        for (const GraphEdge* e : row) {
            AddEdge(e->from, e->to, e->weight);
        }
    }
}

Graph::~Graph() {
    for (size_t i = 0; i < edges.size(); i++) {
        for (size_t j = 0; j < edges[i].size(); j++) {
            delete edges[i][j];
        }
    }
}

void Graph::AddNode(nodekey_t key) {
    if (IsPresent(key)) {
        throw invalid_argument("Node already exists: " + to_string(key));
    }
    keys.push_back(key);
    edges.push_back({});

}

const GraphEdge* Graph::AddEdge(nodekey_t fromNodeKey, nodekey_t toNodeKey, unsigned int weight) {
    if (!IsPresent(fromNodeKey)) { 
        throw invalid_argument("Node does not exist: " + to_string(fromNodeKey));
    }
    if (!IsPresent(toNodeKey)) {
        throw invalid_argument("Node does not exist: " + to_string(toNodeKey));
    }
    size_t index = IndexOf(fromNodeKey);
    for (GraphEdge* e : edges[index]) {
        if (e->to == toNodeKey) {
            throw invalid_argument("Edge already exists");
        }
    }
    GraphEdge* edge = new GraphEdge();
    edge->from = fromNodeKey;
    edge->to = toNodeKey;
    edge->weight = weight;
    edges[index].push_back(edge);
    numEdges++;
    return edge;
}

bool Graph::IsPresent(nodekey_t key) const {
    for (nodekey_t k : keys) {
        if (k == key) {
            return true;
        }
    }
    return false;
}

string Graph::NodesToString() const {
    // size() is unsigned, so size() - 1 would wrap around to a huge number on an empty graph
    if (keys.empty()) {
        return "[]";
    }
    string ans = "[";
    for (size_t i = 0; i < keys.size() - 1; i++) {
        ans += "(" + to_string(keys[i]) + "), ";
    }
    ans += "(" + to_string(keys[keys.size() - 1]) + ")]";
    return ans;
}

string Graph::EdgesToString() const {
    if (edges.empty()) {
        return "[]";
    }
    bool first = true;
    string ans = "[";
    for (size_t i = 0; i < edges.size(); i++) {
        nodekey_t currNode = keys[i];
        for (size_t j = 0; j < edges[i].size(); j++) {
            GraphEdge* currEdge = edges[i][j];
            if (!first) { ans += ", "; }
            ans += "((" + to_string(currNode) + ")->(" + to_string(currEdge->to) + ") w:" + to_string(currEdge->weight) + ")";
            first = false;
        }

    }
    ans += "]";
    return ans;
}

set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t nodeKey) const {
    if (!IsPresent(nodeKey)) { 
        throw invalid_argument("Node does not exist: " + to_string(nodeKey));
    }
    size_t index = IndexOf(nodeKey);
    set<const GraphEdge*> ans;
    for (size_t i = 0; i < edges[index].size(); i++) {
        ans.insert(edges[index][i]);
    }
    return ans;
}

set<nodekey_t> Graph::GetNodes() const {
    set<nodekey_t> ans = {};
    for (nodekey_t k : keys) {
        ans.insert(k);
    }
    return ans;
}

size_t Graph::Size() const {
    return numEdges;
}

size_t Graph::Order() const {
    return keys.size();
}
// Callers must check IsPresent first: a missing key returns keys.size(), which is out of bounds for edges.
size_t Graph::IndexOf(nodekey_t key) const {
    size_t pos = keys.size();
    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key) {
            pos = i;
            break;
        }
    }
    return pos;
}