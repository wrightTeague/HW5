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
    // TODO:
    return "";
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
// Key must always be present!! check IsPresent always
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