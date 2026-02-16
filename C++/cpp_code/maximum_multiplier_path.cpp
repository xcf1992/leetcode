/*
(This question is a variation of the LeetCode question 1514. Path with Maximum Probability. If you haven't completed
that question yet, it is recommended to solve it first.)

Given a directed graph with n nodes labeled from 0 to n−1, where each edge represents an influence relationship between
stocks and carries a multiplier value. Your task is to determine the maximum product of multipliers along any simple
path (i.e., visiting each node at most once) from a given start node to a given end node.

The graph is provided as a list of edges, where each edge is represented as [u, v, w], indicating a directed edge from
node u to node v with a multiplier value w.

Return the maximum product possible from the start node to the end node. If no such simple path exists from the start
node to the end node, return -1.

Constraints:

Each multiplier w is an integer in the range of [1, 105].
The start and end nodes are valid indices within the range [0, n - 1].
The graph may contain cycles, but each edge can be used at most once when calculating the product of multipliers.
Example 1:


Input: n = 5, edges = [[0, 1, 2], [1, 2, 3], [2, 1, 4], [1, 3, 5], [2, 4, 6], [4, 3, 10]], start = 0, end = 3
Output: 360
Explanation: There are two valid simple paths from node 0 to node 3:

Path 0 → 1 → 3 gives a product of 2 × 5 = 10.
Path 0 → 1 → 2 → 4 → 3 gives a product of 2 × 3 × 6 × 10 = 360.
The maximum product among these is 360.
Example 2:

Input: n = 4, edges = [[0, 1, 1], [1, 2, 2], [2, 1, 3], [1, 3, 4]], start = 0, end = 3
Output: 4

Example 3:

Input: n = 6, edges = [[0, 1, 2], [1, 2, 3], [2, 0, 4], [3, 4, 5], [4, 5, 6]], start = 0, end = 3
Output: -1
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
    double maxProduct = -1.0;

    void dfs(int curr, int end, double currentProduct, vector<bool>& visited, vector<vector<pair<int, int>>>& adj) {
        // Base case: reached the destination
        if (curr == end) {
            maxProduct = max(maxProduct, currentProduct);
            return;
        }

        visited[curr] = true;
        for (auto& edge : adj[curr]) {
            int neighbor = edge.first;
            int weight = edge.second;

            if (!visited[neighbor]) {
                dfs(neighbor, end, currentProduct * weight, visited, adj);
            }
        }
        visited[curr] = false;
    }

public:
    double maxMultiplierProduct(int n, vector<vector<int>>& edges, int start, int end) {
        // 1. Build Adjacency List
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        // 2. Setup for DFS
        vector<bool> visited(n, false);
        maxProduct = -1.0;

        // 3. Start Search
        dfs(start, end, 1.0, visited, adj);

        return maxProduct;
    }
};