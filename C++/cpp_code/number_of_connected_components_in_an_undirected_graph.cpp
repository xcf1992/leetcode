/*
323. Number of Connected Components in an Undirected Graph
https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

Given n nodes labeled from 0 to n - 1 and a list of undirected edges
(each edge is a pair of nodes),
write a function to find the number of connected components in an undirected graph.

Example 1:
0        3
|        |
1 --- 2  4
Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.

Example 2:
0           4
|           |
1 --- 2 --- 3
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.

Note:
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1,
0] and thus will not appear together in edges.
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
#include <numeric>
using namespace std;

class Solution {
private:
    int find(int node, vector<int>& parent) {
        if (node != parent[node]) {
            parent[node] = find(parent[node], parent);
        }
        return parent[node];
    }

public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> parent(n, 0);
        iota(parent.begin(), parent.end(), 0);
        int result = n;
        for (vector<int>& edge : edges) {
            int u = find(edge[0], parent);
            int v = find(edge[1], parent);
            if (u != v) {
                parent[u] = v;
                result -= 1;
            }
        }
        return result;
    }
};

class Solution1 {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adj;
        for (auto edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        vector<bool> visited(n, false);
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                continue;
            }

            visited[i] = true;
            result += 1;
            queue<int> connected;
            connected.push(i);
            while (!connected.empty()) {
                int cur = connected.front();
                connected.pop();

                for (int node : adj[cur]) {
                    if (!visited[node]) {
                        visited[node] = true;
                        connected.push(node);
                    }
                }
            }
        }
        return result;
    }
};
