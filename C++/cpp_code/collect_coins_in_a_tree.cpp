/*
https://leetcode.com/problems/collect-coins-in-a-tree/description/
2603. Collect Coins in a Tree

There exists an undirected and unrooted tree with n nodes indexed from 0 to n - 1.
You are given an integer n and a 2D integer array edges of length n - 1,
where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
You are also given an array coins of size n where coins[i] can be either 0 or 1,
where 1 indicates the presence of a coin in the vertex i.
Initially, you choose to start at any vertex in the tree.
Then, you can perform the following operations any number of times:

Collect all the coins that are at a distance of at most 2 from the current vertex, or
Move to any adjacent vertex in the tree.
Find the minimum number of edges you need to go through to collect all the coins and go back to the initial vertex.

Note that if you pass an edge several times, you need to count it into the answer several times.

Example 1:
Input: coins = [1,0,0,0,0,1], edges = [[0,1],[1,2],[2,3],[3,4],[4,5]]
Output: 2
Explanation: Start at vertex 2, collect the coin at vertex 0, move to vertex 3, collect the coin at vertex 5 then move back to vertex 2.
Example 2:
Input: coins = [0,0,0,1,1,0,0,1], edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[5,6],[5,7]]
Output: 2
Explanation: Start at vertex 0, collect the coins at vertices 4 and 3, move to vertex 2,  collect the coin at vertex 7, then move back to vertex 0.

Constraints:
n == coins.length
1 <= n <= 3 * 104
0 <= coins[i] <= 1
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
edges represents a valid tree.
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    // tree pruning + graph traversal
    // 2 phase pruning
    // first:
    // remove all the leaf nodes that do not have any coins

    // second:
    // remove the nodes from which teh coins can be collected by from another nodes ,without traversing them
    // it is basically we can remove two layer of leaf nodes

    int collectTheCoins(vector<int> &coins, vector<vector<int> > &edges) {
        int n = coins.size();
        vector<vector<int>> adj(n);
        vector<int> deg(n);
        for (auto edge: edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++;
            deg[v]++;
        }

        // phase 1 pruning - removing leaf nodes without coins
        queue<int> leaves;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 1 && coins[i] == 0) {
                leaves.push(i);
            }
        }

        while (!leaves.empty()) {
            int u = leaves.front();
            leaves.pop();
            deg[u] = 0; // we removed the node
            for (auto v: adj[u]) {
                if (deg[v] > 0) {
                    deg[v]--;
                    if (deg[v] == 1 && coins[v] == 0) {
                        leaves.push(v);
                    }
                }
            }
        }

        // phase 2 pruning - remove the nodes from where the coins can be collected from its neighbors
        for (int s = 0; s < 2; s++) {
            // since we can move 2 steps, we need to prune 2 times
            for (int i = 0; i < n; i++) {
                if (deg[i] == 1) {
                    leaves.push(i);
                }
            }

            while (!leaves.empty()) {
                int u = leaves.front();
                leaves.pop();
                deg[u] = 0;
                for (auto v: adj[u]) {
                    if (deg[v] > 0) {
                        deg[v]--;
                    }
                }
            }
        }

        // count remaining edges
        int cnt = 0; // number of edges
        for (auto e: edges) {
            if (deg[e[0]] > 0 && deg[e[1]] > 0) {
                cnt++;
            }
            // the nodes with degree>0 are still useful and we need to traverse them
        }
        return cnt * 2;
    }
};
