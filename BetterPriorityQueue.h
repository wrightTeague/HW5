// Author: Teague Wright
// BPQNode struct (BPQNode_struct.txt) and the class declaration line provided by the professor; methods are my own.
// Used Claude (Anthropic) to review my code.

#ifndef BETTERPRIORITYQUEUE_H
#define BETTERPRIORITYQUEUE_H

#include "Graph.h"
#include <queue>

struct BPQNode {
	int pri = INT_MAX;
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;
	
	bool operator<(const BPQNode &other) const {
		return pri < other.pri;
	}

	bool operator>(const BPQNode &other) const {
		return pri > other.pri;
	}
	
	bool operator==(const BPQNode &other) const {
		return this->gnode == other.gnode;
	}
};
class BetterPriorityQueue: public priority_queue<BPQNode, vector<BPQNode>,
greater<BPQNode>>::priority_queue {
    public:

        bool Contains(const BPQNode &n) const; //takes a BPQNode and returns true if that BPQNode is in the queue.
        bool Update(BPQNode n);
        string ToString() const;
        static string BPQNodeToString(BPQNode);
    private:

};
#endif