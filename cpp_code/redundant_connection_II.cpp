/*
685. Redundant Connection II

In this problem, a rooted tree is a directed graph such that,
there is exactly one node (the root) for which all other nodes are descendants of this node,
plus every node has exactly one parent,
except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with N nodes
(with distinct values 1, 2, ..., N),
with one additional directed edge added.
The added edge has two different vertices chosen from 1 to N,
and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges.
Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v,
where u is a parent of child v.

Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes.
If there are multiple answers, return the answer that occurs last in the given 2D-array.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3

Example 2:
Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
    ^    |
    |    v
    4 <- 3

Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
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
#include <map>
#include <set>
#include <numeric>
using namespace std;
/*
There are two cases for the tree structure to be invalid.
1) A node having two parents;
   including corner case: e.g. [[4,2],[1,5],[5,2],[5,3],[2,4]]
2) A circle exists

Consider this case: [[1, 2], [2, 3], [3, 1], [4, 3]].
In this case, can1 = [2, 3], can2 = [4, 3], and one of these two candidates must be the answer.
If we add edges one by one to the empty graph, you'll find that a circle appears after adding [3, 1].
Apparently, can2 is not in the circle.
So can1 is the answer in this case.

 1) Check whether there is a node having two parents.
    If so, store them as candidates A and B, and set the second edge invalid.
 2) Perform normal union find.
    If the tree is now valid
       simply return candidate B
    else if candidates not existing
       we find a circle, return current edge;
    else
       return candidate A instead of B.
*/
class Solution {
private:
    int find(vector<int>& parent, int node) {
        return parent[node] == 0 ? node : find(parent, parent[node]);
    }
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n + 1, 0);
        vector<vector<int>> result;
        for (vector<int>& edge : edges) {
            if (parent[edge[1]] == 0) {
                parent[edge[1]] = edge[0];
            }
            else {
                result.push_back({parent[edge[1]], edge[1]});
                result.push_back(edge);
                edge[1] = 0;
            }
        }

        for (int i = 0; i <= n; i++) {
            parent[i] = 0;
        }
        for (vector<int>& edge : edges) {
            if (edge[1] == 0) {
                continue;
            }

            int u = edge[0];
            int v = edge[1];
            int pu = find(parent, u);
            if (pu == v) {
                if (result.empty()) {
                    return edge;
                }
                // cause currently we have removed result[1] already but still has circle
                return result[0];
            }
            parent[v] = pu;
        }
        return result[1]; // return candidate occur last
    }
};
