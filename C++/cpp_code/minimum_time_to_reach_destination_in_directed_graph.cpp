/*
https://leetcode.com/problems/minimum-time-to-reach-destination-in-directed-graph/description/
3604. Minimum Time to Reach Destination in Directed Graph

You are given an integer n and a directed graph with n nodes labeled from 0 to n - 1. This is represented by a 2D array
edges, where edges[i] = [ui, vi, starti, endi] indicates an edge from node ui to vi that can only be used at any integer
time t such that starti <= t <= endi.

You start at node 0 at time 0.

In one unit of time, you can either:

Wait at your current node without moving, or
Travel along an outgoing edge from your current node if the current time t satisfies starti <= t <= endi.
Return the minimum time required to reach node n - 1. If it is impossible, return -1.



Example 1:

Input: n = 3, edges = [[0,1,0,1],[1,2,2,5]]

Output: 3

Explanation:



The optimal path is:

At time t = 0, take the edge (0 → 1) which is available from 0 to 1. You arrive at node 1 at time t = 1, then wait until
t = 2. At time t = 2, take the edge (1 → 2) which is available from 2 to 5. You arrive at node 2 at time 3. Hence, the
minimum time to reach node 2 is 3.

Example 2:

Input: n = 4, edges = [[0,1,0,3],[1,3,7,8],[0,2,1,5],[2,3,4,7]]

Output: 5

Explanation:



The optimal path is:

Wait at node 0 until time t = 1, then take the edge (0 → 2) which is available from 1 to 5. You arrive at node 2 at t
= 2. Wait at node 2 until time t = 4, then take the edge (2 → 3) which is available from 4 to 7. You arrive at node 3 at
t = 5. Hence, the minimum time to reach node 3 is 5.

Example 3:

Input: n = 3, edges = [[1,0,1,3],[1,2,3,5]]

Output: -1

Explanation:



Since there is no outgoing edge from node 0, it is impossible to reach node 2. Hence, the output is -1.


Constraints:

1 <= n <= 105
0 <= edges.length <= 105
edges[i] == [ui, vi, starti, endi]
0 <= ui, vi <= n - 1
ui != vi
0 <= starti <= endi <= 109
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

class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, pair<int, int>>>> adj(n, vector<pair<int, pair<int, int>>>());
        for (vector<int> e: edges) {
            adj[e[0]].push_back({e[1], {e[2], e[3]}});
        }

        vector<int> min_reach_time(n, INT_MAX);
        min_reach_time[0] = 0;
        queue<pair<int, int>> bfs;
        bfs.push({0, 0});
        while (!bfs.empty()) {
            int cur_node = bfs.front().first;
            int cur_time = bfs.front().second;
            bfs.pop();

            if (cur_time > min_reach_time[cur_node]) {
                continue;
            }

            vector<pair<int, pair<int, int>>>& neighbour = adj[cur_node];
            for (auto& [next_node, time_limit] : neighbour) {
                int start = time_limit.first;
                int end = time_limit.second;
                if (cur_time > end) {
                    continue;
                }

                int move_time = max(start, cur_time);
                // cout << "cur_node = " << cur_node << ", cur_time = " << cur_time << ", next_node = " << next_node << ", start = " << start << ", end = " << end << endl;
                if (move_time + 1 < min_reach_time[next_node]) {
                    min_reach_time[next_node] = move_time + 1;
                    bfs.push({next_node, move_time + 1});
                }
            }
        }

        return min_reach_time[n - 1] == INT_MAX ? -1 : min_reach_time[n - 1];
    }
};

class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        vector<bool> seen(n);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> h;
        h.push({0, 0});
        vector<vector<vector<int>>> G(n);
        for (const auto& edge : edges) {
            G[edge[0]].push_back({edge[1], edge[2], edge[3]});
        }
        while (!h.empty()) {
            auto [t, u] = h.top();
            h.pop();
            if (u == n - 1) {
                return t;
            }
            if (seen[u]) continue;
            seen[u] = true;
            for (const auto& edge : G[u]) {
                int v = edge[0], s = edge[1], e = edge[2];
                if (t <= e) {
                    int t2 = max(s, t) + 1;
                    if (!seen[v]) {
                        h.push({t2, v});
                    }
                }
            }
        }
        return -1;
    }
};