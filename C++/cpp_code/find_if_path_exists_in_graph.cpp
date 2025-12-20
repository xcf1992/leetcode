/*
https://leetcode.com/problems/find-if-path-exists-in-graph/description/
1971. Find if Path Exists in Graph

There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). The edges in
the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge
between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to
itself.

You want to determine if there is a valid path that exists from vertex source to vertex destination.

Given edges and the integers n, source, and destination, return true if there is a valid path from source to
destination, or false otherwise.



Example 1:


Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
Output: true
Explanation: There are two paths from vertex 0 to vertex 2:
- 0 → 1 → 2
- 0 → 2
Example 2:


Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
Output: false
Explanation: There is no path from vertex 0 to vertex 5.


Constraints:

1 <= n <= 2 * 105
0 <= edges.length <= 2 * 105
edges[i].length == 2
0 <= ui, vi <= n - 1
ui != vi
0 <= source, destination <= n - 1
There are no duplicate edges.
There are no self edges.
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

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<bool> visited(n, false);
        visited[source] = true;

        vector<vector<int>> connected(n);
        for (vector<int>& edge : edges) {
            connected[edge[0]].push_back(edge[1]);
            connected[edge[1]].push_back(edge[0]);
        }

        queue<int> bfs;
        bfs.push(source);
        while (!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();

            if (cur == destination) {
                return true;
            }

            for (int nxt : connected[cur]) {
                if (!visited[nxt]) {
                    visited[nxt] = true;
                    bfs.push(nxt);
                }
            }
        }
        return false;
    }
};