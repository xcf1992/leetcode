/*
1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/

Given a weighted undirected connected graph with n vertices numbered from 0 to n-1,
and an array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional
and weighted edge between nodes fromi and toi.
A minimum spanning tree (MST) is a subset of the edges of the graph
that connects all vertices without cycles and with the minimum possible total edge weight.

Find all the critical and pseudo-critical edges in the minimum spanning tree (MST) of the given graph.
An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge.
A pseudo-critical edge, on the other hand, is that which can appear in some MSTs but not all.

Note that you can return the indices of the edges in any order.

Example 1:
Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
Output: [[0,1],[2,3,4,5]]
Explanation: The figure above describes the graph.
The following figure shows all the possible MSTs:

Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first
list of the output. The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical
edges. We add them to the second list of the output.

Example 2:
Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
Output: [[],[0,1,2,3]]
Explanation: We can observe that since all 4 edges have equal weight, choosing any 3 edges from the given 4 will yield
an MST. Therefore all 4 edges are pseudo-critical.

Constraints:
2 <= n <= 100
1 <= edges.length <= min(200, n * (n - 1) / 2)
edges[i].length == 3
0 <= fromi < toi < n
1 <= weighti <= 1000
All pairs (fromi, toi) are distinct.
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
#include <stdio.h>
#include <set>
using namespace std;
/*
We use the standard MST algorithm as a baseline, and denote the total MST weight as origin_mst.
To generate critical and pseudo-critical lists, we enumerate each edge:

If deleting the edge and re-calculating the mst again makes mst total weight increase (or can't form mst),
then the edge goes into critical list.

If we force adding the edge to the mst (by first adding the edge to the mst edge set
and run the standard MST algorithm for the rest of the edges),
and find that the mst doesn't change,
then the edge goes into pseudo-critical list.
(This is because if an edge can be in any mst,
we can always add it to the edge set first,
without changing the final mst total weight).
*/
class UnionFind {
public:
    UnionFind(int n) {
        rank = vector<int>(n, 1);
        f.resize(n);
        for (int i = 0; i < n; ++i)
            f[i] = i;
    }

    int Find(int x) {
        if (x == f[x])
            return x;
        else
            return f[x] = Find(f[x]);
    }

    void Union(int x, int y) {
        int fx = Find(x), fy = Find(y);
        if (fx == fy)
            return;
        if (rank[fx] > rank[fy])
            swap(fx, fy);
        f[fx] = fy;
        if (rank[fx] == rank[fy])
            rank[fy]++;
    }

private:
    vector<int> f, rank;
};

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        for (int i = 0; i < edges.size(); ++i) {
            edges[i].push_back(i);
        }
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; });
        int origin_mst = GetMST(n, edges, -1);
        vector<int> critical, non_critical;
        for (int i = 0; i < edges.size(); ++i) {
            if (origin_mst < GetMST(n, edges, i)) {
                critical.push_back(edges[i][3]);
            } else if (origin_mst == GetMST(n, edges, -1, i)) {
                non_critical.push_back(edges[i][3]);
            }
        }
        return {critical, non_critical};
    }

private:
    int GetMST(const int n, const vector<vector<int>>& edges, int blockedge, int pre_edge = -1) {
        UnionFind uf(n);
        int weight = 0;
        if (pre_edge != -1) {
            weight += edges[pre_edge][2];
            uf.Union(edges[pre_edge][0], edges[pre_edge][1]);
        }
        for (int i = 0; i < edges.size(); ++i) {
            if (i == blockedge)
                continue;
            const auto& edge = edges[i];
            if (uf.Find(edge[0]) == uf.Find(edge[1]))
                continue;
            uf.Union(edge[0], edge[1]);
            weight += edge[2];
        }
        for (int i = 0; i < n; ++i) {
            if (uf.Find(i) != uf.Find(0))
                return 1e9 + 7;
        }
        return weight;
    }
};
