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

/*
Assume a node is root and apply bfs search,
where we recode the:

dis[i] is the distance from root to i
fa[i] is the father of i
If two points met up and they are not father-son relation,
they met in a cycle.
The distance of circly is smaller or equal than dis[i] + dis[j] + 1.

To check the father-son relation, there some different ways:

we can use an array fa[i] to save the father of each node.
we can add (i, father) to the queue
we can also check dis[i] <= dis[j]
We iterate all nodes as root, and we can return the minimum circle.

The Core Insight
When we encounter a neighbor that's already been visited (dist[neighbour] != INT_MAX), there are two possibilities:

The neighbor is our parent in the BFS tree (the node we just came from)
The neighbor was reached via a different path (indicating a cycle)

Why dist[cur] <= dist[neighbour] Works
In BFS from a source node:

Nodes are visited in order of increasing distance
A parent node always has distance exactly 1 less than its child
So if we're at cur and see a visited neighbour, we check:

If dist[cur] <= dist[neighbour]:

This means neighbour is NOT our parent (parent would have dist[neighbour] = dist[cur] - 1)
This means we've found an alternative path to neighbour
This creates a cycle!

If dist[cur] > dist[neighbour] (the opposite):

This would mean dist[neighbour] < dist[cur]
This is likely our parent node in the BFS tree
We should ignore it (it's just the edge we came from)
*/
class Solution {
private:
    void bfs(int src, int n, int& rst, vector<vector<int>>& adj) {
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        queue<int> q;
        q.push(src);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int neighbour : adj[cur]) {
                if (dist[neighbour] == INT_MAX) {
                    dist[neighbour] = dist[cur] + 1;
                    q.push(neighbour);
                } else if (dist[cur] <= dist[neighbour]) {
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