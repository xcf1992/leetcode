/*
https://leetcode.com/problems/number-of-good-paths/description/
2421. Number of Good Paths

There is a tree (i.e. a connected, undirected graph with no cycles) consisting of n nodes numbered from 0 to n - 1 and
exactly n - 1 edges.

You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node. You are also
given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes
ai and bi.

A good path is a simple path that satisfies the following conditions:

The starting node and the ending node have the same value.
All nodes between the starting node and the ending node have values less than or equal to the starting node (i.e. the
starting node's value should be the maximum value along the path). Return the number of distinct good paths.

Note that a path and its reverse are counted as the same path. For example, 0 -> 1 is considered to be the same as 1 ->
0. A single node is also considered as a valid path.



Example 1:


Input: vals = [1,3,2,1,3], edges = [[0,1],[0,2],[2,3],[2,4]]
Output: 6
Explanation: There are 5 good paths consisting of a single node.
There is 1 additional good path: 1 -> 0 -> 2 -> 4.
(The reverse path 4 -> 2 -> 0 -> 1 is treated as the same as 1 -> 0 -> 2 -> 4.)
Note that 0 -> 2 -> 3 is not a good path because vals[2] > vals[0].
Example 2:


Input: vals = [1,1,2,2,3], edges = [[0,1],[1,2],[2,3],[2,4]]
Output: 7
Explanation: There are 5 good paths consisting of a single node.
There are 2 additional good paths: 0 -> 1 and 2 -> 3.
Example 3:


Input: vals = [1], edges = []
Output: 1
Explanation: The tree consists of only one node, so there is one good path.


Constraints:

n == vals.length
1 <= n <= 3 * 104
0 <= vals[i] <= 105
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
edges represents a valid tree.
*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
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
    int find_parent(int cur, vector<int>& parent) {
        if (parent[cur] == -1) {
            return cur;
        }

        parent[cur] = find_parent(parent[cur], parent);
        return parent[cur];
    }
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        map<int, vector<int>> same_val_nodes;
        for (int i = 0; i < n; i++) {
            same_val_nodes[vals[i]].push_back(i);
        }

        vector<vector<int>> adj(n);
        for (vector<int>& e : edges) {
            if (vals[e[0]] >= vals[e[1]]) {
                adj[e[0]].push_back(e[1]);
            }
            if (vals[e[1]] >= vals[e[0]]) {
                adj[e[1]].push_back(e[0]);
            }
        }

        // union find
        int rst = 0;
        vector<int> parent(n, -1);
        for (auto& [val, nodes] : same_val_nodes) {
            for (int node : nodes) {
                int parent_node = find_parent(node, parent);
                for (int neighbour : adj[node]) {
                    int parent_neighbour = find_parent(neighbour, parent);
                    if (parent_neighbour != parent_node) {
                        parent[parent_neighbour] = parent_node;
                    }
                }
            }

            unordered_map<int, int> group;
            for (int node : nodes) {
                group[find_parent(node, parent)] += 1;
            }

            rst += nodes.size(); // good path with single node
            for (auto& [_, cnt] : group) {
                rst += cnt * (cnt - 1) / 2;
            }
        }
        return rst;
    }
};