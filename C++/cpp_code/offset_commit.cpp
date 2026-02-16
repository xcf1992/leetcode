/*
This problem is a popular Robinhood interview question often called "Offset Ordering" or "Message Committing."
It tests your ability to handle data streams and state management efficiently.
Full Problem DescriptionThe goal is to simulate a message acknowledgment (commit) system.

Stream: Messages are identified by non-negative integers called offsets, starting
from 0 ($0, 1, 2, \dots$).

Out-of-Order Processing: Because of multi-threading, messages can finish processing in any
order.

Commit Rules:An offset $X$ can only be committed if all offsets smaller than $X$ have already been committed.A
commit represents the "furthest point" the system has successfully acknowledged. For example, committing offset 2
implies that 0, 1, and 2 are all done.

The Task: Given a list of offsets in the order they finish processing, return a
list of the same length where each element is:The highest offset committed at that moment.-1 if no new commit can be
made because a lower offset is still missing.ExampleInput: [2, 0, 1]Process 2: Cannot commit because 0 and 1 are
missing.

Output: -1.Process 0: 0 is the start. We commit 0. Output: 0.Process 1: Now 0, 1, and 2 are all processed. The
highest contiguous offset is 2. Output: 2.Result: [-1, 0, 2]C++ SolutionWe use a Min-Heap (Priority Queue) or a Boolean
Array/Set to track "ready" offsets that are waiting for their predecessors. We also maintain a next_to_commit variable.
*/
#include <iostream>
#include <vector>
#include <unordered_set>

std::vector<int> solveOffsetCommit(const std::vector<int>& processed_offsets) {
    std::vector<int> results;
    // Tracks offsets that finished but are blocked by smaller missing offsets
    std::unordered_set<int> seen;

    int next_to_commit = 0;  // We are waiting for this specific offset
    int last_committed = -1; // The highest offset we've actually acknowledged

    for (int offset : processed_offsets) {
        seen.insert(offset);

        // If the offset we just received is the one we were waiting for
        if (offset == next_to_commit) {
            // "Greedily" advance the commit pointer as far as possible
            while (seen.count(next_to_commit)) {
                last_committed = next_to_commit;
                next_to_commit += 1;
            }
            results.push_back(last_committed);
        } else {
            // We are still missing an earlier offset
            results.push_back(-1);
        }
    }

    return results;
}

int main() {
    std::vector<int> input = {2, 0, 1, 5, 4, 3};
    std::vector<int> output = solveOffsetCommit(input);

    // Expected: [-1, 0, 2, -1, -1, 5]
    for (int x : output) {
        std::cout << x << " ";
    }
    return 0;
}