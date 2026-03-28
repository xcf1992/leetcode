/*
https://leetcode.com/problems/minimize-the-maximum-edge-weight-of-graph/description/
3419. Minimize the Maximum Edge Weight of Graph

You are given two integers, n and threshold, as well as a directed weighted graph of n nodes numbered from 0 to n - 1.
The graph is represented by a 2D integer array edges, where edges[i] = [Ai, Bi, Wi] indicates that there is an edge
going from node Ai to node Bi with weight Wi.

You have to remove some edges from this graph (possibly none), so that it satisfies the following conditions:

Node 0 must be reachable from all other nodes.
The maximum edge weight in the resulting graph is minimized.
Each node has at most threshold outgoing edges.
Return the minimum possible value of the maximum edge weight after removing the necessary edges. If it is impossible for
all conditions to be satisfied, return -1.



Example 1:

Input: n = 5, edges = [[1,0,1],[2,0,2],[3,0,1],[4,3,1],[2,1,1]], threshold = 2

Output: 1

Explanation:



Remove the edge 2 -> 0. The maximum weight among the remaining edges is 1.

Example 2:

Input: n = 5, edges = [[0,1,1],[0,2,2],[0,3,1],[0,4,1],[1,2,1],[1,4,1]], threshold = 1

Output: -1

Explanation:

It is impossible to reach node 0 from node 2.

Example 3:

Input: n = 5, edges = [[1,2,1],[1,3,3],[1,4,5],[2,3,2],[3,4,2],[4,0,1]], threshold = 1

Output: 2

Explanation:



Remove the edges 1 -> 3 and 1 -> 4. The maximum weight among the remaining edges is 2.

Example 4:

Input: n = 5, edges = [[1,2,1],[1,3,3],[1,4,5],[2,3,2],[4,0,1]], threshold = 1

Output: -1



Constraints:

2 <= n <= 105
1 <= threshold <= n - 1
1 <= edges.length <= min(105, n * (n - 1) / 2).
edges[i].length == 3
0 <= Ai, Bi < n
Ai != Bi
1 <= Wi <= 106
There may be multiple edges between a pair of nodes, but they must have unique weights.
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
Intuition: we can ignore threshold because we only need one edge to connect a node (directly or indirectly) to node
zero.

Approach
We build a reversed adjacency list ral. We then run dfs from node zero, and count nodes we can reach while limiting
weight to m.

Then, we binary-search for the smallest weight that allows us to reach all nodes.
题目要求每个节点出边最多 threshold 个，而 threshold >= 1。我们最终需要的是一棵以节点 0 为根的入树（所有节点都能到达
0）。在这棵树中，每个非根节点恰好贡献一条出边（指向父节点的那条）。1 <= threshold，所以树结构天然满足 threshold 约束。
换句话说，树是最"省"的连通结构，每个节点只用一条出边，不可能违反 threshold >= 1 的限制。
 */
class Solution {
private:
    bool can_reach_all(vector<vector<pair<int, int>>>& adj, int n, int limit) {
        vector<bool> visited(n, false);
        visited[0] = true;

        stack<int> stk;
        stk.push(0);

        int cnt = 1;
        while (!stk.empty()) {
            int cur = stk.top();
            stk.pop();
            for (auto& [nxt, weight] : adj[cur]) {
                if (weight > limit || visited[nxt]) {
                    continue;
                }

                visited[nxt] = true;
                stk.push(nxt);
                cnt += 1;
            }
        }
        return cnt == n;
    }
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        int left = 0;
        int right = 0;
        vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());
        for (vector<int>& e : edges) {
            adj[e[1]].push_back({e[0], e[2]});
            right = max(right, e[2]);
        }

        if (!can_reach_all(adj, n, right)) {
            return -1;
        }

        int rst = right;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (can_reach_all(adj, n, mid)) {
                rst = mid;
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return rst;
    }
};
