/*
https://leetcode.com/problems/minimum-edge-reversals-so-every-node-is-reachable/description/
2858. Minimum Edge Reversals So Every Node Is Reachable

There is a simple directed graph with n nodes labeled from 0 to n - 1. The graph would form a tree if its edges were
bi-directional.

You are given an integer n and a 2D integer array edges, where edges[i] = [ui, vi] represents a directed edge going from
node ui to node vi.

An edge reversal changes the direction of an edge, i.e., a directed edge going from node ui to node vi becomes a
directed edge going from node vi to node ui.

For every node i in the range [0, n - 1], your task is to independently calculate the minimum number of edge reversals
required so it is possible to reach any other node starting from node i through a sequence of directed edges.

Return an integer array answer, where answer[i] is the minimum number of edge reversals required so it is possible to
reach any other node starting from node i through a sequence of directed edges.



Example 1:



Input: n = 4, edges = [[2,0],[2,1],[1,3]]
Output: [1,1,0,2]
Explanation: The image above shows the graph formed by the edges.
For node 0: after reversing the edge [2,0], it is possible to reach any other node starting from node 0.
So, answer[0] = 1.
For node 1: after reversing the edge [2,1], it is possible to reach any other node starting from node 1.
So, answer[1] = 1.
For node 2: it is already possible to reach any other node starting from node 2.
So, answer[2] = 0.
For node 3: after reversing the edges [1,3] and [2,1], it is possible to reach any other node starting from node 3.
So, answer[3] = 2.
Example 2:



Input: n = 3, edges = [[1,2],[2,0]]
Output: [2,0,1]
Explanation: The image above shows the graph formed by the edges.
For node 0: after reversing the edges [2,0] and [1,2], it is possible to reach any other node starting from node 0.
So, answer[0] = 2.
For node 1: it is already possible to reach any other node starting from node 1.
So, answer[1] = 0.
For node 2: after reversing the edge [1, 2], it is possible to reach any other node starting from node 2.
So, answer[2] = 1.


Constraints:

2 <= n <= 105
edges.length == n - 1
edges[i].length == 2
0 <= ui == edges[i][0] < n
0 <= vi == edges[i][1] < n
ui != vi
The input is generated such that if the edges were bi-directional, the graph would be a tree.
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

/*
root the tree at 0.
find subtree[i] which is the number of reversal to traverse to all nodes in the subtree of i.
answer[root] is actually subtree[root].
for each child node i, answer[i] = subtree[i] + (from i to parent[i]) + (parent[i] to all other nodes not in
subtree[i]). the last part is answer[parent[i]] - (from parent[i] to i) - subtree[i]. Does not seem to suffer from star
trees.
 */
class Solution {
private:
    void dfs_1(int cur, int parent, vector<int>& rst) {
        for (pair<int, int>& nxt : graph_[cur]) {
            if (nxt.first == parent) {
                continue;
            }

            if (nxt.second == -1) {
                rst[0] += 1;
            }

            dfs_1(nxt.first, cur, rst);
        }
    }

    void dfs_2(int cur, int parent, vector<int>& rst) {
        for (pair<int, int>& nxt : graph_[cur]) {
            if (nxt.first == parent) {
                continue;
            }

            rst[nxt.first] = rst[cur] + nxt.second;
            dfs_2(nxt.first, cur, rst);
        }
    }

public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        graph_ = vector<vector<pair<int, int>>>(n, vector<pair<int, int>>());
        for (size_t i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            graph_[u].push_back({v, 1});
            graph_[v].push_back({u, -1});
        }

        vector<int> rst(n, 0);
        dfs_1(0, -1, rst);   // get the result for node 0
        dfs_2(0, -1, rst);  // update result for other nodes
        return rst;
    }

private:
    vector<vector<pair<int, int>>> graph_;
};

/*
Intuition

We need to reach every node from node i.
This means there will be no incoming edges to i.
This means i should be the root node.
The answer will be number of reversed edges while traversing the entire tree starting from node i.
Can brute force work?

We need answer for each i through [0,n)
DFS from each node i will take O(n)
The solution will be 0(n
2
 ). Hence, brute force will not work.
How to optimize?

We are traversing the entire tree irrespective of the directed nature.
In a tree, every node has only one parent. Think why?
The tree is always fixed. We are not modifying the tree.
So, during DFS, our recursive call will look like - dfs(node,parent).
Since, we are traversing the tree n times, there will be overlapping subproblems, where we would be calculating the
answer again and again. Why not cache this?

The solution is a good but actuallly TLE soluiton.
In the case of [[0,1],[0,2],[0,3]....[0,n-1]],
each edge will be picked in each call of dfs,
it will become O(n^2) in total.

One solution is get the result for one root,
then pass the result in the tree by one more dfs.
*/
class Solution {
private:
    int dfs(int cur, int parent) {
        int cnt = 0;
        if (dp_.find({cur, parent}) != dp_.end()) {
            return dp_[{cur, parent}];
        }

        for (int& nxt : graph_[cur]) {
            if (nxt == parent) {
                continue;
            }
            cnt += dfs(nxt, cur);
        }

        for (int& nxt : reverse_graph_[cur]) {
            if (nxt == parent) {
                continue;
            }
            cnt += dfs(nxt, cur) + 1;
        }

        dp_[{cur, parent}] = cnt;
        return dp_[{cur, parent}];
    }

public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        graph_ = vector<vector<int>>(n, vector<int>());
        reverse_graph_ = vector<vector<int>>(n, vector<int>());
        dp_.clear();

        for (vector<int> edge : edges) {
            graph_[edge[0]].push_back(edge[1]);
            reverse_graph_[edge[1]].push_back(edge[0]);
        }

        vector<int> rst;
        for (int i = 0; i < n; i++) {
            rst.push_back(dfs(i, -1));
        }
        return rst;
    }

private:
    vector<vector<int>> graph_;
    vector<vector<int>> reverse_graph_;
    map<pair<int, int>, int> dp_;
};