/*
1719. Number Of Ways To Reconstruct A Tree
https://leetcode.com/problems/number-of-ways-to-reconstruct-a-tree/

You are given an array pairs, where pairs[i] = [xi, yi], and:
There are no duplicates.
xi < yi
Let ways be the number of rooted trees that satisfy the following conditions:
The tree consists of nodes whose values appeared in pairs.
A pair [xi, yi] exists in pairs if and only if xi is an ancestor of yi or yi is an ancestor of xi.
Note: the tree does not have to be a binary tree.
Two ways are considered to be different if there is at least one node that has different parents in both ways.
Return:
0 if ways == 0
1 if ways == 1
2 if ways > 1
A rooted tree is a tree that has a single root node, and all edges are oriented to be outgoing from the root.
An ancestor of a node is any node on the path from the root to that node (excluding the node itself).
The root has no ancestors.

Example 1:
Input: pairs = [[1,2],[2,3]]
Output: 1
Explanation: There is exactly one valid rooted tree, which is shown in the above figure.
Example 2:
Input: pairs = [[1,2],[2,3],[1,3]]
Output: 2
Explanation: There are multiple valid rooted trees. Three of them are shown in the above figures.
Example 3:
Input: pairs = [[1,2],[2,3],[2,4],[1,5]]
Output: 0
Explanation: There are no valid rooted trees.

Constraints:
1 <= pairs.length <= 105
1 <= xi < yi <= 500
The elements in pairs are unique.
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
#include <numeric>
using namespace std;

class Solution {
public:
    int checkWays(vector<vector<int>>& pairs) {
        unordered_map<int, unordered_set<int>> adj;
        for (int i = 0; i < pairs.size(); i++) {
            adj[pairs[i][0]].emplace(pairs[i][1]);
            adj[pairs[i][1]].emplace(pairs[i][0]);
        }

        priority_queue<pair<int, int>> q;
        for (auto& [x, arr] : adj) {
            q.push({arr.size(), x});
        }

        int n = q.size();
        bool multiple = false;
        unordered_set<int> seen;
        while (!q.empty()) {
            auto [sz, v] = q.top();
            q.pop();

            int u = 0;
            int usz = n + 1;
            if (!seen.empty()) {
                for (auto x : adj[v]) {
                    if (adj[x].size() < usz && seen.count(x)) {
                        u = x;
                        usz = adj[x].size();
                    }
                }
            }

            seen.emplace(v);
            if (u == 0) {
                if (sz != (n - 1)) {
                    return 0;
                }
                continue;
            }


            for (auto x : adj[v]) {
                if (x == u) {
                    continue;
                }

                if (!adj[u].count(x)) {
                    return 0;
                }
            }

            if (usz == sz) {
                multiple = true;
            }
        }

        if (multiple) {
            return 2;
        }

        return 1;
    }
};
