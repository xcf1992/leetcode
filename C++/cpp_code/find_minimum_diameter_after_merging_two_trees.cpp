/*
https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/description/
3203. Find Minimum Diameter After Merging Two Trees

There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m - 1, respectively. You are
given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi]
indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there
is an edge between nodes ui and vi in the second tree.

You must connect one node from the first tree with another node from the second tree with an edge.

Return the minimum possible diameter of the resulting tree.

The diameter of a tree is the length of the longest path between any two nodes in the tree.



Example 1:

Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]

Output: 3

Explanation:

We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.

Example 2:


Input: edges1 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]

Output: 5

Explanation:

We can obtain a tree of diameter 5 by connecting node 0 from the first tree with node 0 from the second tree.



Constraints:

1 <= n, m <= 105
edges1.length == n - 1
edges2.length == m - 1
edges1[i].length == edges2[i].length == 2
edges1[i] = [ai, bi]
0 <= ai, bi < n
edges2[i] = [ui, vi]
0 <= ui, vi < m
The input is generated such that edges1 and edges2 represent valid trees.
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
    // return the farthest node and distance
    pair<int, int> bfs(vector<vector<int>>& adj, int n, int start) {
        vector<int> dist(n, -1);
        dist[start] = 0;

        queue<int> q;
        q.push(start);

        int farthest = start;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int nxt : adj[cur]) {
                if (dist[nxt] == -1) {
                    dist[nxt] = dist[cur] + 1;
                    q.push(nxt);

                    if (dist[nxt] > dist[farthest]) {
                        farthest = nxt;
                    }
                }
            }
        }
        return {farthest, dist[farthest]};
    }

    int get_diameter(vector<vector<int>>& adj, int n) {
        if (n <= 1) {
            return 0;
        }

        auto [end_p1, _] = bfs(adj, n, 0);
        auto [end_p2, dist] = bfs(adj, n, end_p1);
        return dist;
    }
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;

        vector<vector<int>> adj1(n, vector<int>());
        for (vector<int>& e : edges1) {
            adj1[e[0]].push_back(e[1]);
            adj1[e[1]].push_back(e[0]);
        }

        vector<vector<int>> adj2(m, vector<int>());
        for (vector<int>& e : edges2) {
            adj2[e[0]].push_back(e[1]);
            adj2[e[1]].push_back(e[0]);
        }

        int d1 = get_diameter(adj1, n);
        int d2 = get_diameter(adj2, m);
        int merged_d = (d1 + 1) / 2 + (d2 + 1) / 2 + 1; // +1 is the connected edge to merge the tree
        return max({d1, d2, merged_d});
    }
};