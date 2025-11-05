/*
https://leetcode.com/problems/minimize-maximum-component-cost
3613. Minimize Maximum Component Cost
You are given an undirected connected graph with n nodes labeled from 0 to n - 1 and a 2D integer array edges where edges[i] = [ui, vi, wi] denotes an undirected edge between node ui and node vi with weight wi, and an integer k.

You are allowed to remove any number of edges from the graph such that the resulting graph has at most k connected components.

The cost of a component is defined as the maximum edge weight in that component. If a component has no edges, its cost is 0.

Return the minimum possible value of the maximum cost among all components after such removals.



Example 1:

Input: n = 5, edges = [[0,1,4],[1,2,3],[1,3,2],[3,4,6]], k = 2

Output: 4

Explanation:



Remove the edge between nodes 3 and 4 (weight 6).
The resulting components have costs of 0 and 4, so the overall maximum cost is 4.
Example 2:

Input: n = 4, edges = [[0,1,5],[1,2,5],[2,3,5]], k = 1

Output: 5

Explanation:



No edge can be removed, since allowing only one component (k = 1) requires the graph to stay fully connected.
That single component’s cost equals its largest edge weight, which is 5.


Constraints:

1 <= n <= 5 * 104
0 <= edges.length <= 105
edges[i].length == 3
0 <= ui, vi < n
1 <= wi <= 106
1 <= k <= n
The input graph is connected.
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
#include <set>
#include <map>
#include <numeric>
using namespace std;

class Solution {
private:
    int find_parent(int cur, vector<int> &parent) {
        if (parent[cur] == -1) {
            return cur;
        }

        parent[cur] = find_parent(parent[cur], parent);
        return parent[cur];
    }

public:
    int minCost(int n, vector<vector<int> > &edges, int k) {
        if (n <= k) {
            return 0;
        }

        sort(edges.begin(), edges.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[2] < b[2];
        });

        vector<int> parent(n, -1);
        int cnt = n;
        for (const vector<int> &e: edges) {
            int u = find_parent(e[0], parent);
            int v = find_parent(e[1], parent);
            if (u != v) {
                parent[u] = v;
                cnt -= 1;
            }
            if (cnt <= k) {
                return e[2];
            }
        }
        return -1;
    }
};