/*
https://www.hack2hire.com/companies/openai/coding-questions/69a3c4396e73e4abccc9c14c/practice?questionId=69a3c6546e73e4abccc9c150

You are implementing a shard management system for a distributed key-value store. The system distributes data across
multiple shards given in the format "<id>:<start>:<end>". Each shard is responsible for a contiguous range of integer
keys, represented by an inclusive interval [start, end].

To balance the load effectively, the system enforces a limit on the maximum number of shards that can cover any single
key. Your task is to implement the rebalance(limit, shards) method, which resolves overlapping intervals that exceed the
limit and fills any gaps between the overall covered ranges.

To minimize data movement across the distributed system, you must follow these deterministic rules during rebalancing:

Processing Order: Iterate through the existing shards sorted primarily by their start boundary (ascending) and
secondarily by their end boundary (ascending). Resolve Overlaps (Shift): If a key is already covered by limit active
shards, any subsequent shard attempting to cover this key must have its start boundary shifted to the right. It should
start at the earliest possible key where the coverage is strictly less than limit. Delete Excess (Drop): If shifting a
shard's start boundary to the right causes its start to be strictly greater than its original end, the shard is
completely eclipsed and must be deleted from the system. Fill Gaps (Extend): The global coverage of keys must remain
continuous from the absolute minimum start to the absolute maximum end of the initial shards. If a gap exists between
the current contiguous coverage and the next shard's start, extend the end boundary of the most recently processed
active shard to bridge the gap. Return the updated internal state of the shards based on these rules. You may return the
result in any order.

Constraints:

0 ≤ limit ≤ 105
0 ≤ shards.length ≤ 104
-109 ≤ start, end ≤ 109
start ≤ end
Identifiers are distinct and contain no colons.
Example 1:

Input: limit = 2, shards = ["A:0:100", "B:40:110", "C:80:200", "D:210:300"]
Output: ["A:0:100", "B:40:110", "C:101:209", "D:210:300"]
Explanation: Keys [0, 100] are covered by A and B. Shard C overlaps keys [80, 100] which are already at capacity, so its
start shifts to 101. A gap exists between C (ending at 200) and D (starting at 210), so C is extended to 209.

Example 2:

Input: limit = 1, shards = ["A:0:100", "B:80:180"]
Output: ["A:0:100", "B:101:180"]

Example 3:

Input: limit = 2, shards = ["A:0:30", "B:0:31", "C:0:32", "D:0:100"]
Output: ["A:0:30", "B:0:31", "C:31:32", "D:32:100"]
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
#include <sstream>
using namespace std;

struct Shard {
    string id;
    int start;
    int end;

    Shard();
    Shard(string id_, string start_, string end_) : id(id_) {
        start = stoi(start_);
        end = stoi(end_);
    };

    string to_string() {
        return id + ":" + std::to_string(start) + ":" + std::to_string(end);
    }
};

class Solution {
public:
    vector<string> rebalance(int limit, vector<string> input) {
        vector<Shard> all_shards;
        for (string& in : input) {
            vector<string> tokens;
            int pos = in.find(':');
            while (pos != string::npos) {
                tokens.push_back(in.substr(0, pos));
                in = in.substr(pos + 1);
                pos = in.find(':');
            }
            tokens.push_back(in);
            all_shards.push_back(Shard(tokens[0], tokens[1], tokens[2]));
        }

        sort(all_shards.begin(), all_shards.end(),
             [](Shard& a, Shard& b) { return a.start < b.start || (a.start == b.start && a.end < b.end); });

        priority_queue<int, vector<int>, greater<int>> min_end_heap;
        int last_start = INT_MIN;
        vector<Shard> accepted;
        for (Shard& shard : all_shards) {
            int new_start = max(last_start, shard.start);
            // pop out all the events ended already
            while (!min_end_heap.empty() && min_end_heap.top() < new_start) {
                min_end_heap.pop();
            }

            while (min_end_heap.size() >= limit) {
                new_start = min_end_heap.top() + 1;
                min_end_heap.pop();
            }

            if (new_start > shard.end) {
                continue;
            }

            shard.start = new_start;
            min_end_heap.push(shard.end);
            last_start = shard.start;
            accepted.push_back(shard);
        }

        // fill gaps and extent last shard to max_end
        if (!accepted.empty()) {
            int covered_end = accepted[0].end;
            for (int i = 1; i < accepted.size(); i++) {
                Shard& prev = accepted[i - 1];
                Shard& cur = accepted[i];
                if (cur.start > covered_end + 1) {
                    prev.end = cur.start - 1;
                    covered_end = prev.end;
                }
                if (cur.end > covered_end) {
                    covered_end = cur.end;
                }
            }
        }

        vector<string> rst;
        for (Shard& shard : accepted) {
            rst.push_back(shard.to_string());
        }
        return rst;
    }
};