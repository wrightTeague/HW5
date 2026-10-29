// Author: Teague Wright
// Used Claude (Anthropic) to generate the initial empty method stubs and to review my code.

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
    if ()
    return false;
}

string BetterPriorityQueue::ToString() const {
    // TODO:
    return "";
}

string BetterPriorityQueue::BPQNodeToString(BPQNode n) {
    // TODO:
    return "";
}
