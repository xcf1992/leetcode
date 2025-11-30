/*
1245. Tree Diameter
https://leetcode.com/problems/tree-diameter/

Given an undirected tree, return its diameter:
the number of edges in a longest path in that tree.

The tree is given as an array of edges where edges[i] = [u, v] is a bidirectional edge between nodes u and v.
Each node has labels in the set {0, 1, ..., edges.length}.

Example 1:
  --- 1
0
  ----2
Input: edges = [[0,1],[0,2]]
Output: 2
Explanation:
A longest path of the tree is the path 1 - 0 - 2.

Example 2:
Input: edges = [[0,1],[1,2],[2,3],[1,4],[4,5]]
Output: 4
Explanation:
A longest path of the tree is the path 3 - 2 - 1 - 4 - 5.

Constraints:
0 <= edges.length < 10^4
edges[i][0] != edges[i][1]
0 <= edges[i][j] <= edges.length
The given edges form an undirected tree.
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
#include <numeric>
using namespace std;

class Solution {
private:
    int dfs(unordered_map<int, vector<int>>& graph, int& result, int cur, int parent) {
        int longestLen = 0;
        int longerLen = 0;
        for (int nxt : graph[cur]) {
            if (nxt == parent) {
                continue;
            }

            int length = dfs(graph, result, nxt, cur);
            if (length > longestLen) {
                longerLen = longestLen;
                longestLen = length;
            } else if (length > longerLen) {
                longerLen = length;
            }
            result = max(result, 1 + longerLen + longestLen);
        }
        return longestLen + 1;
    }

public:
    int treeDiameter(vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> graph;
        for (vector<int>& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        int result = 0;
        dfs(graph, result, 0, -1);
        return result - 1;
    }
};