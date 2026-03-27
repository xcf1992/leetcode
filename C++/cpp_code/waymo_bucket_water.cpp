/*
given a number of buckets of different size, how to use the bucket so the total volume that the buckets adds up to a
certain target, a buckets can be pulling in water , or pull out water to get to the target。
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <climits>
#include <map>
#include <cassert>
using namespace std;

/*
这题本质就是一个变体的 subset sum 问题：每个桶有三种选择——不用、加水（+volume）、抽水（-volume），问能否凑出目标值
target。 比如 buckets = [3, 5, 7], target = 9：选 +3, -5, +7 → 3 - 5 + 7 = 5，不行。选 +7, +5, -3 → 9，可以。 这跟经典
subset sum 的区别就是每个元素有三种状态而不是两种，但 DP 思路一样，用一个 set 记录所有可达的 sum。
*/

class Solution {
public:
    bool solve(vector<int> buckets, int target) {
        int n = buckets.size();
        // dp[sum] = true if reachable
        unordered_set<int> reachable_volume;
        reachable_volume.insert(0);

        // parent[sum] = {previous_sum, choice} for path reconstruction
        unordered_map<int, pair<int, int>> parent;  // sum -> {prev_sum, choice}
        for (int i = 0; i < n; i++) {
            unordered_set<int> next_dp;
            for (int vol : reachable_volume) {
                // choice 1: skip this bucket
                if (next_dp.find(vol) == next_dp.end()) {
                    next_dp.insert(vol);
                }

                // choice 2: pour in (+)
                next_dp.insert(vol + buckets[i]);
            }
        }
    }
};
