// Author: Teague Wright
// Used Claude (Anthropic) to explain the algorithm and review my code. Claude wrote the unreachable-node
// check and the Big-O comment.

#include "Dijkstra.h"
#include "BetterPriorityQueue.h"

using namespace std;

int dijkstra(nodekey_t start, nodekey_t end, const Graph *g) {
    // Big-O: O(V^2 + E*V), where V = nodes and E = edges. Both the Graph and the BPQ use linear scans.
    // - Filling the queue is O(V log V), and the up to V pops are O(log V) each.
    // - GetOutwardEdgesFrom is O(V) to find the node (keys is unsorted), called once per pop: O(V^2).
    //   Copying its edges into a set adds O(E log V) in total.
    // - Update is O(V) to find the node in c (percolating is only O(log V)), called once per edge: O(E*V).
    // The V^2 and E*V terms dominate the rest.
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
        // INT_MAX is the smallest pri left, so nothing remaining is reachable. Stopping here also keeps
        // INT_MAX + weight from overflowing into a negative distance.
        if (currNode.gnode == end || currNode.pri == INT_MAX) {
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
    return INT_MAX; // end isn't in the graph, so there's no path to it
}
