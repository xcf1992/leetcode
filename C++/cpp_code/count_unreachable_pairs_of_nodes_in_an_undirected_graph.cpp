/*
https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/

2316. Count Unreachable Pairs of Nodes in an Undirected Graph
You are given an integer n. There is an undirected graph with n nodes, numbered from 0 to n - 1. You are given a 2D
integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.

Return the number of pairs of different nodes that are unreachable from each other.



Example 1:


Input: n = 3, edges = [[0,1],[0,2],[1,2]]
Output: 0
Explanation: There are no pairs of nodes that are unreachable from each other. Therefore, we return 0.
Example 2:


Input: n = 7, edges = [[0,2],[0,5],[2,4],[1,6],[5,4]]
Output: 14
Explanation: There are 14 pairs of nodes that are unreachable from each other:
[[0,1],[0,3],[0,6],[1,2],[1,3],[1,4],[1,5],[2,3],[2,6],[3,4],[3,5],[3,6],[4,6],[5,6]].
Therefore, we return 14.


Constraints:

1 <= n <= 105
0 <= edges.length <= 2 * 105
edges[i].length == 2
0 <= ai, bi < n
ai != bi
There are no repeated edges.
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
    int find_parent(int cur, vector<int>& parent) {
        if (parent[cur] == -1) {
            return cur;
        }
        parent[cur] = find_parent(parent[cur], parent);
        return parent[cur];
    }

public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        vector<int> parent(n, -1);
        unordered_map<int, int> group;
        for (const vector<int>& edge : edges) {
            int u = find_parent(edge[0], parent);
            int v = find_parent(edge[1], parent);
            if (u == v) {
                continue;
            }
            parent[u] = v;
        }

        for (int i = 0; i < n; i++) {
            int cur_parent = find_parent(i, parent);
            if (group.find(cur_parent) == group.end()) {
                group[cur_parent] = 0;
            }
            group[cur_parent] += 1;
        }

        long long result = 0;
        int other_cnt = n;
        for (auto it = group.begin(); it != group.end(); it++) {
            int cur_cnt = it->second;
            other_cnt -= cur_cnt;
            result += cur_cnt * other_cnt;
        }
        return result;
    }
};
