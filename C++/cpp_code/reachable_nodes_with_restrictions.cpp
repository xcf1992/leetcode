/*
https://leetcode.com/problems/reachable-nodes-with-restrictions/description/
2368. Reachable Nodes With Restrictions

There is an undirected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.

You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between
nodes ai and bi in the tree. You are also given an integer array restricted which represents restricted nodes.

Return the maximum number of nodes you can reach from node 0 without visiting a restricted node.

Note that node 0 will not be a restricted node.



Example 1:


Input: n = 7, edges = [[0,1],[1,2],[3,1],[4,0],[0,5],[5,6]], restricted = [4,5]
Output: 4
Explanation: The diagram above shows the tree.
We have that [0,1,2,3] are the only nodes that can be reached from node 0 without visiting a restricted node.
Example 2:


Input: n = 7, edges = [[0,1],[0,2],[0,5],[0,4],[3,2],[6,5]], restricted = [4,2,1]
Output: 3
Explanation: The diagram above shows the tree.
We have that [0,5,6] are the only nodes that can be reached from node 0 without visiting a restricted node.


Constraints:

2 <= n <= 105
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
edges represents a valid tree.
1 <= restricted.length < n
1 <= restricted[i] < n
All the values of restricted are unique.
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
    int dfs(int prev, int cur, vector<vector<int>>& node_to_children, unordered_set<int>& restricted_nodes) {
        if (restricted_nodes.find(cur) != restricted_nodes.end()) {
            return 0;
        }

        int cnt = 1;
        for (int child : node_to_children[cur]) {
            if (child == prev) {
                continue;
            }
            cnt += dfs(cur, child, node_to_children, restricted_nodes);
        }
        return cnt;
    }
public:
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        unordered_set<int> restricted_nodes(restricted.begin(), restricted.end());
        vector<vector<int>> node_to_children(n, vector<int>());
        for (vector<int>& e : edges) {
            node_to_children[e[0]].push_back(e[1]);
            node_to_children[e[1]].push_back(e[0]);
        }

        return dfs(-1, 0, node_to_children, restricted_nodes);
    }
};
