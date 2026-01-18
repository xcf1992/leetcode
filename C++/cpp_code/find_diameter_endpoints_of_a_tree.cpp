/*
https://leetcode.com/problems/find-diameter-endpoints-of-a-tree/description/
3787. Find Diameter Endpoints of a Tree

You are given an undirected tree with n nodes, numbered from 0 to n - 1. It is represented by a 2D integer array
edges​​​​​​​ of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai
and bi in the tree.

A node is called special if it is an endpoint of any diameter path of the tree.

Return a binary string s of length n, where s[i] = '1' if node i is special, and s[i] = '0' otherwise.

A diameter path of a tree is the longest simple path between any two nodes. A tree may have multiple diameter paths.

An endpoint of a path is the first or last node on that path.



Example 1:



Input: n = 3, edges = [[0,1],[1,2]]

Output: "101"

Explanation:

The diameter of this tree consists of 2 edges.
The only diameter path is the path from node 0 to node 2
The endpoints of this path are nodes 0 and 2, so they are special.
Example 2:



Input: n = 7, edges = [[0,1],[1,2],[2,3],[3,4],[3,5],[1,6]]

Output: "1000111"

Explanation:

The diameter of this tree consists of 4 edges. There are 4 diameter paths:

The path from node 0 to node 4
The path from node 0 to node 5
The path from node 6 to node 4
The path from node 6 to node 5
The special nodes are nodes 0, 4, 5, 6, as they are endpoints in at least one diameter path.

Example 3:

​​​​​​​

Input: n = 2, edges = [[0,1]]

Output: "11"

Explanation:

The diameter of this tree consists of 1 edge.
The only diameter path is the path from node 0 to node 1
The endpoints of this path are nodes 0 and 1, so they are special.


Constraints:

2 <= n <= 105
edges.length == n - 1
edges[i] = [ai, bi]
0 <= ai, bi < n
The input is generated such that edges represents a valid tree.
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
Intuition
In a tree, if you start from any node u and go to a farthest node v, then v must be an endpoint of a diameter. Moreover,
if you then start from that endpoint v and go to its farthest nodes, those nodes are exactly the other possible diameter
endpoints. Therefore, the union of:

all nodes farthest from u (candidates on one side), and
all nodes farthest from v (candidates on the opposite side),
gives precisely the set of all diameter endpoints (nodes that can appear as an endpoint of some longest path).
So we can:

DFS from 0 to get distances and find the maximum distance mx1 and one farthest node v.
Mark every node at distance mx1 from 0 as special.
DFS from v to get distances and the maximum distance mx2.
Mark every node at distance mx2 from v as special.
*/
class Solution {
private:
    void bfs(int n, int start, vector<int>& furthest, vector<vector<int>>& connect) {
        vector<bool> visited(n, false);
        visited[start] = true;

        queue<int> bfs;
        bfs.push(start);

        while (!bfs.empty()) {
            int cur_size = bfs.size();
            furthest.clear();
            for (int i = 0; i < cur_size; i++) {
                int cur = bfs.front();
                bfs.pop();

                furthest.push_back(cur);
                for (int next : connect[cur]) {
                    if (visited[next]) {
                        continue;
                    }

                    visited[next] = true;
                    bfs.push(next);
                }
            }
        }
    }

public:
    string findSpecialNodes(int n, vector<vector<int>>& edges) {
        vector<vector<int>> connect(n, vector<int>());
        for (vector<int>& e : edges) {
            connect[e[0]].push_back(e[1]);
            connect[e[1]].push_back(e[0]);
        }

        vector<int> furthest;
        bfs(n, 0, furthest, connect);

        vector<int> candidates;
        bfs(n, furthest[0], candidates, connect);

        string rst(n, '0');
        for (int idx : candidates) {
            rst[idx] = '1';
            vector<int> endpoints;
            bfs(n, idx, endpoints, connect);
            for (int node : endpoints) {
                rst[node] = '1';
            }
        }
        return rst;
    }
};