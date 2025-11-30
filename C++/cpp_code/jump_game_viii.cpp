/*
https://leetcode.com/problems/jump-game-viii/description/
2297. Jump Game VIII

You are given a 0-indexed integer array nums of length n. You are initially standing at index 0. You can jump from index
i to index j where i < j if:

nums[i] <= nums[j] and nums[k] < nums[i] for all indexes k in the range i < k < j, or
nums[i] > nums[j] and nums[k] >= nums[i] for all indexes k in the range i < k < j.
You are also given an integer array costs of length n where costs[i] denotes the cost of jumping to index i.

Return the minimum cost to jump to the index n - 1.



Example 1:

Input: nums = [3,2,4,4,1], costs = [3,7,6,4,2]
Output: 8
Explanation: You start at index 0.
- Jump to index 2 with a cost of costs[2] = 6.
- Jump to index 4 with a cost of costs[4] = 2.
The total cost is 8. It can be proven that 8 is the minimum cost needed.
Two other possible paths are from index 0 -> 1 -> 4 and index 0 -> 2 -> 3 -> 4.
These have a total cost of 9 and 12, respectively.
Example 2:

Input: nums = [0,1,2], costs = [1,1,1]
Output: 2
Explanation: Start at index 0.
- Jump to index 1 with a cost of costs[1] = 1.
- Jump to index 2 with a cost of costs[2] = 1.
The total cost is 2. Note that you cannot jump directly from index 0 to index 2 because nums[0] <= nums[1].


Constraints:

n == nums.length == costs.length
1 <= n <= 105
0 <= nums[i], costs[i] <= 105
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& costs) {
        int n = nums.size();
        vector<int> next_bigger_idx(n, -1);
        vector<int> next_less_idx(n, -1);
        stack<int> min_stk;
        stack<int> max_stk;
        for (int i = n - 1; i >= 0; --i) {
            while (!min_stk.empty() && nums[i] > nums[min_stk.top()]) {
                min_stk.pop();
            }
            if (!min_stk.empty()) {
                next_bigger_idx[i] = min_stk.top();
            }
            min_stk.push(i);

            while (!max_stk.empty() && nums[i] <= nums[max_stk.top()]) {
                max_stk.pop();
            }
            if (!max_stk.empty()) {
                next_less_idx[i] = max_stk.top();
            }
            max_stk.push(i);
        }

        vector<long long> min_cost(n, LONG_LONG_MAX);
        min_cost[0] = 0;
        queue<int> bfs;
        bfs.push(0);
        while (!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();

            if (next_bigger_idx[cur] != -1) {
                int nxt = next_bigger_idx[cur];
                if (min_cost[nxt] > min_cost[cur] + costs[nxt]) {
                    min_cost[nxt] = min_cost[cur] + costs[nxt];
                    bfs.push(nxt);
                }
            }

            if (next_less_idx[cur] != -1) {
                int nxt = next_less_idx[cur];
                if (min_cost[nxt] > min_cost[cur] + costs[nxt]) {
                    min_cost[nxt] = min_cost[cur] + costs[nxt];
                    bfs.push(nxt);
                }
            }
        }
        return min_cost[n - 1];
    }
};
