/*
https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/description/
3372. Maximize the Number of Target Nodes After Connecting Trees I

There exist two undirected trees with n and m nodes, with distinct labels in ranges [0, n - 1] and [0, m - 1], respectively.

You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree. You are also given an integer k.

Node u is target to node v if the number of edges on the path from u to v is less than or equal to k. Note that a node is always target to itself.

Return an array of n integers answer, where answer[i] is the maximum possible number of nodes target to node i of the first tree if you have to connect one node from the first tree to another node in the second tree.

Note that queries are independent from each other. That is, for every query you will remove the added edge before proceeding to the next query.



Example 1:

Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2

Output: [9,7,9,8,8]

Explanation:

For i = 0, connect node 0 from the first tree to node 0 from the second tree.
For i = 1, connect node 1 from the first tree to node 0 from the second tree.
For i = 2, connect node 2 from the first tree to node 4 from the second tree.
For i = 3, connect node 3 from the first tree to node 4 from the second tree.
For i = 4, connect node 4 from the first tree to node 4 from the second tree.

Example 2:

Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]], k = 1

Output: [6,3,3,3,3]

Explanation:

For every i, connect node i of the first tree with any node of the second tree.




Constraints:

2 <= n, m <= 1000
edges1.length == n - 1
edges2.length == m - 1
edges1[i].length == edges2[i].length == 2
edges1[i] = [ai, bi]
0 <= ai, bi < n
edges2[i] = [ui, vi]
0 <= ui, vi < m
The input is generated such that edges1 and edges2 represent valid trees.
0 <= k <= 1000
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
private:
    void build(vector<vector<int>>& edges, vector<vector<int>>& graph) {
        for (const vector<int>& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
    }

    void count_target(vector<vector<int>>& graph, vector<int>& target_cnt, int distance) {
        int total = target_cnt.size();
        for (int root = 0; root < total; root++) {
            queue<int> bfs;
            vector<bool> visited(total, false);

            bfs.push(root);
            int cur_dis = 0;
            while (!bfs.empty() && cur_dis <= distance) {
                int cur_size = bfs.size();
                cur_dis += 1;
                for (int i = 0; i < cur_size; i++) {
                    int cur = bfs.front();
                    bfs.pop();

                    target_cnt[root] += 1;
                    visited[cur] = true;

                    if (cur_dis > distance) {
                        continue;
                    }

                    for (int nxt : graph[cur]) {
                        if (!visited[nxt]) {
                            bfs.push(nxt);
                        }
                    }
                }
            }
        }
    }
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;

        vector<vector<int>> graph1(n);
        build(edges1, graph1);
        vector<vector<int>> graph2(m);
        build(edges2, graph2);

        vector<int> target_cnt1(n, 0);
        count_target(graph1, target_cnt1, k);
        vector<int> target_cnt2(m, 0);
        count_target(graph2, target_cnt2, k - 1);

        int max_cnt = *max_element(target_cnt2.begin(), target_cnt2.end());
        vector<int> result(n, 0);
        for (int i = 0; i < n; i++) {
            result[i] = target_cnt1[i] + max_cnt;
        }
        return result;
    }
};
