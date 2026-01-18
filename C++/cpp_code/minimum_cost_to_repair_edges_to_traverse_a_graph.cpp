/*
https://leetcode.com/problems/minimum-cost-to-repair-edges-to-traverse-a-graph/description/
3807. Minimum Cost to Repair Edges to Traverse a Graph

You are given an undirected graph with n nodes labeled from 0 to n - 1. The graph consists of m edges represented by a
2D integer array edges, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with a
repair cost of wi.

You are also given an integer k. Initially, all edges are damaged.

You may choose a non-negative integer money and repair all edges whose repair cost is less than or equal to money. All
other edges remain damaged and cannot be used.

You want to travel from node 0 to node n - 1 using at most k edges.

Return an integer denoting the minimum amount of money required to make this possible, or return -1 if it is impossible.



Example 1:



Input: n = 3, edges = [[0,1,10],[1,2,10],[0,2,100]], k = 1

Output: 100

Explanation:

The only valid path using at most k = 1 edge is 0 -> 2, which requires repairing the edge with cost 100. Therefore, the
minimum required amount of money is 100.

Example 2:



Input: n = 6, edges = [[0,2,5],[2,3,6],[3,4,7],[4,5,5],[0,1,10],[1,5,12],[0,3,9],[1,2,8],[2,4,11]], k = 2

Output: 12

Explanation:

With money = 12, all edges with repair cost at most 12 become usable.
This allows the path 0 -> 1 -> 5, which uses exactly 2 edges and reaches node 5.
If money < 12, there is no available path of length at most k = 2 from node 0 to node 5.
Therefore, the minimum required money is 12.
Example 3:

​​​​​​​

Input: n = 3, edges = [[0,1,1]], k = 1

Output: -1

Explanation:

It is impossible to reach node 2 from node 0 using any amount of money. Therefore, the answer is -1.



Constraints:

2 <= n <= 5 * 104
1 <= edges.length == m <= 105
edges[i] = [ui, vi, wi]
0 <= ui, vi < n
1 <= wi <= 109
1 <= k <= n
There are no self-loops or duplicate edges in the graph.
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
using namespace std;

class Solution {
private:
    bool can_reach(int max_cost, int k, vector<vector<pair<int, int>>>& conn) {
        int n = conn.size();
        vector<bool> visited(n, false);
        visited[0] = true;
        queue<pair<int, int>> q;
        q.push({0, 0});
        while (!q.empty()) {
            int cur = q.front().first;
            int cnt = q.front().second;
            q.pop();

            if (cur == n - 1) {
                return true;
            }

            if (cnt >= k) {
                continue;
            }

            for (auto& [next, cost] : conn[cur]) {
                if (visited[next]) {
                    continue;
                }

                if (cost > max_cost) {
                    continue;
                }

                visited[next] = true;
                q.push({next, cnt + 1});
            }
        }
        return false;
    }
public:
    int minCost(int n, vector<vector<int>>& edges, int k) {
        vector<vector<pair<int, int>>> conn(n, vector<pair<int, int>>());
        int max_cost = INT_MIN;
        for (vector<int>& e: edges) {
            conn[e[0]].push_back({e[1], e[2]});
            conn[e[1]].push_back({e[0], e[2]});
            max_cost = max(max_cost, e[2]);
        }

        int left = 0;
        int right = max_cost + 1;
        int rst = INT_MAX;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (can_reach(mid, k, conn)) {
                rst = mid;
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return rst == INT_MAX ? -1 : rst;
    }
};