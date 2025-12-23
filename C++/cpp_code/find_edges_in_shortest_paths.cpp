/*
https://leetcode.com/problems/find-edges-in-shortest-paths/description
3123. Find Edges in Shortest Paths

You are given an undirected weighted graph of n nodes numbered from 0 to n - 1. The graph consists of m edges
represented by a 2D array edges, where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi
with weight wi.

Consider all the shortest paths from node 0 to node n - 1 in the graph. You need to find a boolean array answer where
answer[i] is true if the edge edges[i] is part of at least one shortest path. Otherwise, answer[i] is false.

Return the array answer.

Note that the graph may not be connected.



Example 1:


Input: n = 6, edges = [[0,1,4],[0,2,1],[1,3,2],[1,4,3],[1,5,1],[2,3,1],[3,5,3],[4,5,2]]

Output: [true,true,true,false,true,true,true,false]

Explanation:

The following are all the shortest paths between nodes 0 and 5:

The path 0 -> 1 -> 5: The sum of weights is 4 + 1 = 5.
The path 0 -> 2 -> 3 -> 5: The sum of weights is 1 + 1 + 3 = 5.
The path 0 -> 2 -> 3 -> 1 -> 5: The sum of weights is 1 + 1 + 2 + 1 = 5.
Example 2:


Input: n = 4, edges = [[2,0,1],[0,1,1],[0,3,4],[3,2,2]]

Output: [true,false,false,true]

Explanation:

There is one shortest path between nodes 0 and 3, which is the path 0 -> 2 -> 3 with the sum of weights 1 + 2 = 3.



Constraints:

2 <= n <= 5 * 104
m == edges.length
1 <= m <= min(5 * 104, n * (n - 1) / 2)
0 <= ai, bi < n
ai != bi
1 <= wi <= 105
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
#include <climits>
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> connected(n, vector<pair<int, int>>());
        for (int i = 0; i < edges.size(); i++) {
            connected[edges[i][0]].push_back({edges[i][1], i});
            connected[edges[i][1]].push_back({edges[i][0], i});
        }

        vector<int> min_distance(n, INT_MAX);
        min_distance[0] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0}); // distance, vertex

        while (!pq.empty()) {
            int cur = pq.top().second;
            int dist = pq.top().first;
            pq.pop();

            if (dist > min_distance[cur]) {
                continue;
            }

            for (pair<int, int>& edge : connected[cur]) {
                int nxt = edge.first;
                int edge_idx = edge.second;
                if (min_distance[nxt] > min_distance[cur] + edges[edge_idx][2]) {
                    min_distance[nxt] = min_distance[cur] + edges[edge_idx][2];
                    pq.push({min_distance[nxt], nxt});
                }
            }
        }

        int edge_cnt = edges.size();
        vector<bool> rst(edge_cnt, false);

        if (min_distance[n - 1] == INT_MAX) {
            return rst;
        }

        vector<bool> visited(n, false);
        visited[n - 1] = true;
        pq.push({min_distance[n - 1], n - 1});
        while (!pq.empty()) {
            int cur = pq.top().second;
            int dist = pq.top().first;
            pq.pop();

            for (pair<int, int>& edge : connected[cur]) {
                int nxt = edge.first;
                int edge_idx = edge.second;
                if (dist - edges[edge_idx][2] == min_distance[nxt]) {
                    if (!visited[nxt]) {
                        pq.push({min_distance[nxt], nxt});
                    }
                    visited[nxt] = true;
                    rst[edge_idx] = true;
                }
            }
        }
        return rst;
    }
};
