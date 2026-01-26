/*
https://leetcode.com/problems/shortest-cycle-in-a-graph/description/
2608. Shortest Cycle in a Graph

There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1. The edges in the graph
are represented by a given 2D integer array edges, where edges[i] = [ui, vi] denotes an edge between vertex ui and
vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.

Return the length of the shortest cycle in the graph. If no cycle exists, return -1.

A cycle is a path that starts and ends at the same node, and each edge in the path is used only once.



Example 1:


Input: n = 7, edges = [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]]
Output: 3
Explanation: The cycle with the smallest length is : 0 -> 1 -> 2 -> 0
Example 2:


Input: n = 4, edges = [[0,1],[0,2]]
Output: -1
Explanation: There are no cycles in this graph.


Constraints:

2 <= n <= 1000
1 <= edges.length <= 1000
edges[i].length == 2
0 <= ui, vi < n
ui != vi
There are no repeated edges.
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
using namespace std;

class Solution {
private:
    void bfs(int src, int n, int& rst, vector<vector<int>>& adj) {
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        vector<int> parent(n, -1);

        queue<int> q;
        q.push(src);
        while(!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int neighbour : adj[cur]) {
                if (dist[neighbour] == INT_MAX) {
                    dist[neighbour] = dist[cur] + 1;
                    parent[neighbour] = cur;
                    q.push(neighbour);
                } else if (parent[cur] != neighbour && parent[neighbour] != cur) {
                    rst = min(rst, dist[cur] + dist[neighbour] + 1);
                }
            }
        }
    }
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n, vector<int>());
        for (vector<int> e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int rst = INT_MAX;
        for (int i = 0; i < n; i++) {
            bfs(i, n, rst, adj);
        }
        return rst == INT_MAX ? -1 : rst;
    }
};