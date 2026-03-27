/*
https://leetcode.com/problems/find-closest-node-to-given-two-nodes/description/
2359. Find Closest Node to Given Two Nodes

You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.

The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from
node i to node edges[i]. If there is no outgoing edge from i, then edges[i] == -1.

You are also given two integers node1 and node2.

Return the index of the node that can be reached from both node1 and node2, such that the maximum between the distance
from node1 to that node, and from node2 to that node is minimized. If there are multiple answers, return the node with
the smallest index, and if no possible answer exists, return -1.

Note that edges may contain cycles.



Example 1:


Input: edges = [2,2,3,-1], node1 = 0, node2 = 1
Output: 2
Explanation: The distance from node 0 to node 2 is 1, and the distance from node 1 to node 2 is 1.
The maximum of those two distances is 1. It can be proven that we cannot get a node with a smaller maximum distance than
1, so we return node 2. Example 2:


Input: edges = [1,2,-1], node1 = 0, node2 = 2
Output: 2
Explanation: The distance from node 0 to node 2 is 2, and the distance from node 2 to itself is 0.
The maximum of those two distances is 2. It can be proven that we cannot get a node with a smaller maximum distance than
2, so we return node 2.


Constraints:

n == edges.length
2 <= n <= 105
-1 <= edges[i] < n
edges[i] != i
0 <= node1, node2 < n
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
/*
The basic approach here is that we run two dfs's from each node to calculate the distance to every reachable node from
it. So for every node i we look at the maximum of these two distances (from the dfs's) and we pick the node where
that maximum is minimized.
 */
class Solution {
private:
    void dfs(vector<int>& edges, int cur, int dist, vector<int>& min_dist) {
        if (cur == -1) {
            return;
        }

        if (min_dist[cur] != INT_MAX) {
            return;
        }

        min_dist[cur] = dist;
        dfs(edges, edges[cur], dist + 1, min_dist);
    }
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        vector<int> min_dist_1(n, INT_MAX);
        min_dist_1[node1] = 0;
        vector<int> min_dist_2(n, INT_MAX);
        min_dist_2[node2] = 0;

        dfs(edges, edges[node1], 1, min_dist_1);
        dfs(edges, edges[node2], 1, min_dist_2);

        int min_dist = INT_MAX;
        int rst = -1;
        for (int i = 0; i < n; i++) {
            if (min_dist_1[i] == INT_MAX || min_dist_2[i] == INT_MAX) {
                continue;
            }

            int max_dist = max(min_dist_1[i], min_dist_2[i]);
            if (max_dist < min_dist) {
                min_dist = max_dist;
                rst = i;
            }
        }
        return rst;
    }
};
