/*
https://leetcode.com/problems/longest-cycle-in-a-graph/description/
2360. Longest Cycle in a Graph

You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.

The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from
node i to node edges[i]. If there is no outgoing edge from node i, then edges[i] == -1.

Return the length of the longest cycle in the graph. If no cycle exists, return -1.

A cycle is a path that starts and ends at the same node.



Example 1:


Input: edges = [3,3,4,2,3]
Output: 3
Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
The length of this cycle is 3, so 3 is returned.
Example 2:


Input: edges = [2,-1,3,1]
Output: -1
Explanation: There are no cycles in this graph.


Constraints:

n == edges.length
2 <= n <= 105
-1 <= edges[i] < n
edges[i] != i
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Solution {
    void get_cycle(vector<int>& edges, int cur, vector<bool>& visited, vector<int>& path, int& rst) {
        if (cur == -1) {
            return;
        }

        if (!visited[cur]) {
            visited[cur] = true;
            path.push_back(cur);
            get_cycle(edges, edges[cur], visited, path, rst);
            return;
        }

        int count = -1;
        for (int i = 0; i < path.size(); i++) {
            if (path[i] == cur) {
                count = i;
                break;
            }
        }

        if (count == -1) {
            return;
        }
        rst = max(rst, (int)path.size() - count);
    }

public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<bool> visited(n, 0);
        int rst = -1;
        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                continue;
            }

            vector<int> path;
            get_cycle(edges, i, visited, path, rst);
        }

        return rst;
    }
};
