/*
https://leetcode.com/problems/maximize-sum-of-weights-after-edge-removals/description
3367. Maximize Sum of Weights after Edge Removals

There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n -
1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi in the tree.

Your task is to remove zero or more edges such that:

Each node has an edge with at most k other nodes, where k is given.
The sum of the weights of the remaining edges is maximized.
Return the maximum possible sum of weights for the remaining edges after making the necessary removals.



Example 1:

Input: edges = [[0,1,4],[0,2,2],[2,3,12],[2,4,6]], k = 2

Output: 22

Explanation:



Node 2 has edges with 3 other nodes. We remove the edge [0, 2, 2], ensuring that no node has edges with more than k = 2
nodes. The sum of weights is 22, and we can't achieve a greater sum. Thus, the answer is 22. Example 2:

Input: edges = [[0,1,5],[1,2,10],[0,3,15],[3,4,20],[3,5,5],[0,6,10]], k = 3

Output: 65

Explanation:

Since no node has edges connecting it to more than k = 3 nodes, we don't remove any edges.
The sum of weights is 65. Thus, the answer is 65.


Constraints:

2 <= n <= 105
1 <= k <= n - 1
edges.length == n - 1
edges[i].length == 3
0 <= edges[i][0] <= n - 1
0 <= edges[i][1] <= n - 1
1 <= edges[i][2] <= 106
The input is generated such that edges form a valid tree.
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
#include <stdio.h>
using namespace std;

/*
Explanation
Build the graph G,
where G[i] is the list of children [j, w].

the helper function dfs(i) will return v1 and v2,
v1 is the weight sum of node i with atmost k - 1 children.
v2 is the weight sum of node i with atmost k children.

For each node i,
we recursively call dfs on its children,
compare the diff v1 + w and v2 for each child,
and pick k - 1 and k biggest improvement separately.

Finally return dfs(0)[1].

sumWeights += dp[nxt][0];:
It initializes a base sum, $sumWeights$,
by accumulating $dp[nxt][0]$ for all children $nxt$.Interpretation:
$dp[nxt][0]$ is the maximum weight sum in the child's subtree
when we can pick up to $k$ edges in that subtree.
By summing these, $sumWeights$ represents the total maximum weight sum in $cur$'s entire subtree
(excluding $cur$'s edges to children for now), assuming we don't keep any of the edges $(cur, nxt)$.
 */
class Solution {
    void dfs(vector<vector<pair<int, int>>>& adj, int cur, int parent, int k, vector<vector<long long>>& dp) {
        vector<long long> differences;
        long long sumWeights = 0;

        // Explore all neighbors of the current node
        for (auto [nxt, weight] : adj[cur]) {
            if (nxt == parent) {
                continue;  // Skip the parent node to avoid backtracking
            }

            dfs(adj, nxt, cur, k, dp);  // Recursively process the child node

            // Difference in weight contribution between keeping and removing the edge
            differences.push_back(weight + dp[nxt][1] - dp[nxt][0]);

            // Accumulate the base case sum (dp[v][0]) for the subtree rooted at v
            sumWeights += dp[nxt][0];
        }

        // Sort differences in descending order to prioritize edges with higher contributions
        sort(rbegin(differences), rend(differences));

        // Case 1: Select at most `k` edges for the current node
        dp[cur][0] = sumWeights;
        for (int i = 0; i < min(k, (int)differences.size()); ++i) {
            if (differences[i] > 0)
                dp[cur][0] += differences[i];
        }

        // Case 2: Select at most `k-1` edges for the current node (for parent inclusion)
        dp[cur][1] = sumWeights;
        for (int i = 0; i < min(k - 1, (int)differences.size()); ++i) {
            if (differences[i] > 0)
                dp[cur][1] += differences[i];
        }
    }

public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size() + 1;  // Total nodes in the tree
        vector<vector<pair<int, int>>> adj(n);

        // Build adjacency list
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        // dp[u][0]: Maximum sum when at most `k` edges are selected for node `u`
        // dp[u][1]: Maximum sum when at most `k-1` edges are selected for node `u` (to consider parent inclusion)
        vector<vector<long long>> dp(n, vector<long long>(2, -1));

        // Start DFS from the root node (0)
        dfs(adj, 0, -1, k, dp);

        // The result is the maximum sum when starting from the root node with at most `k` edges
        return dp[0][0];
    }
};
