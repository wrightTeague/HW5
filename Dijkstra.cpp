// Author: Teague Wright
// Used Claude (Anthropic) to review my code.
// TODO: Big-O analysis (required by the spec)

#include "Dijkstra.h"
#include "BetterPriorityQueue.h"

using namespace std;

int dijkstra(nodekey_t start, nodekey_t end, const Graph *g) {
    BetterPriorityQueue Q = {};
    set<nodekey_t> s = g->GetNodes();
    for (nodekey_t n : s) {
        BPQNode temp;
        temp.gnode = n;
        if (n == start) {
            temp.pri = 0;
        }
        Q.push(temp);
    }
    while (!Q.empty()) {
        BPQNode currNode = Q.top();
        Q.pop();
        if (currNode.gnode == end) {
            return currNode.pri;
        }
        set<const GraphEdge*> edges = g->GetOutwardEdgesFrom(currNode.gnode);
        for (const GraphEdge* e : edges) {
            int candidate = currNode.pri + e->weight;
            BPQNode temp;
            temp.gnode = e->to;
            temp.pri = candidate;
            Q.Update(temp);
        }
    }
    return 0;
}
