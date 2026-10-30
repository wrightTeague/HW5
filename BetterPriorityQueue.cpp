// Author: Teague Wright
// Used Claude (Anthropic) to generate the initial empty method stubs and to review my code. Claude added the comments in Update.

#include "BetterPriorityQueue.h"

using namespace std;

bool BetterPriorityQueue::Contains(const BPQNode &n) const {
    for (const BPQNode &node : this->c) {
        if (n == node) {
            return true;
        }
    }
    return false;
}

bool BetterPriorityQueue::Update(BPQNode n) {
    if (!Contains(n)) {
        return false;
    }
    size_t index = ULLONG_MAX;
    for (size_t i = 0; i < this->c.size(); i++) {
        if (this->c[i] == n) {
            index = i;
            break;
        }
    }
    // Dijkstra only ever lowers a distance, so a larger priority is ignored on purpose (BPQTests requires this).
    if (n.pri >= this->c[index].pri) {
        return false;
    } else {
        // A smaller priority can't break the heap below this node, so it only ever needs to move up.
        this->c[index].pri = n.pri;
        while (index != 0) {
            size_t parent = (index - 1) / 2;
            if (this->c[parent].pri > n.pri) {
                std::swap(this->c[parent], this->c[index]);
                index = parent;
            } else {
                break;
            }
        }
    }
    return true;
}

string BetterPriorityQueue::ToString() const {
    if (c.empty()) {
        return "[]";
    }
    bool first = true;
    string ans = "[";
    for (BPQNode n : c) {
        if (!first) { ans += ", "; }
        ans += BPQNodeToString(n);
        first = false;
    }
    return ans += "]";
}

string BetterPriorityQueue::BPQNodeToString(BPQNode n) {
    return "(" + to_string(n.gnode) + ", pri: " + to_string(n.pri) + ")";
}