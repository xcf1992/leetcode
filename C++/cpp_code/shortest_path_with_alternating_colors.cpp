/*
1129. Shortest Path with Alternating Colors
Consider a directed graph, with nodes labelled 0, 1, ..., n-1.
In this graph, each edge is either red or blue, and there could be self-edges or parallel edges.

Each [i, j] in red_edges denotes a red directed edge from node i to node j.
Similarly, each [i, j] in blue_edges denotes a blue directed edge from node i to node j.

Return an array answer of length n,
where each answer[X] is the length of the shortest path from node 0 to node X
such that the edge colors alternate along the path (or -1 if such a path doesn't exist).

Example 1:

Input: n = 3, red_edges = [[0,1],[1,2]], blue_edges = []
Output: [0,1,-1]
Example 2:

Input: n = 3, red_edges = [[0,1]], blue_edges = [[2,1]]
Output: [0,1,-1]
Example 3:

Input: n = 3, red_edges = [[1,0]], blue_edges = [[2,1]]
Output: [0,-1,-1]
Example 4:

Input: n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
Output: [0,1,2]
Example 5:

Input: n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
Output: [0,1,1]


Constraints:

1 <= n <= 100
red_edges.length <= 400
blue_edges.length <= 400
red_edges[i].length == blue_edges[i].length == 2
0 <= red_edges[i][j], blue_edges[i][j] < n
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        vector<vector<vector<int>>> connections(2, vector<vector<int>>(n, vector<int>()));
        for (vector<int>& edge : red_edges) {
            connections[0][edge[0]].push_back(edge[1]);
        }
        for (vector<int>& edge : blue_edges) {
            connections[1][edge[0]].push_back(edge[1]);
        }

        vector<vector<int>> distance(2, vector<int>(n, INT_MAX));
        distance[0][0] = distance[1][0] = 0;
        queue<vector<int>> bfs;
        bfs.push({0, 0, 0}); // {curPos, curDistance, curColor}
        bfs.push({0, 0, 1});
        while (!bfs.empty()) {
            int cur = bfs.front()[0];
            int dis = bfs.front()[1];
            int clr = bfs.front()[2];
            bfs.pop();
            for (int next : connections[1 - clr][cur]) {
                if (dis + 1 < distance[1 - clr][next]) {
                    distance[1 - clr][next] = 1 + dis;
                    bfs.push({next, dis + 1, 1 - clr});
                }
            }
        }

        vector<int> result(n, 0);
        for (int i = 1; i < n; ++i) {
            result[i] = min(distance[0][i], distance[1][i]);
            if (result[i] == INT_MAX) {
                result[i] = -1;
            }
        }
        return result;
    }
};
