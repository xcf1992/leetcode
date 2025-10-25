/*
https://leetcode.com/problems/power-grid-maintenance

3607. Power Grid Maintenance

You are given an integer c representing c power stations, each with a unique identifier id from 1 to c (1‑based indexing).

These stations are interconnected via n bidirectional cables, represented by a 2D array connections, where each element connections[i] = [ui, vi] indicates a connection between station ui and station vi. Stations that are directly or indirectly connected form a power grid.

Initially, all stations are online (operational).

You are also given a 2D array queries, where each query is one of the following two types:

[1, x]: A maintenance check is requested for station x. If station x is online, it resolves the check by itself. If station x is offline, the check is resolved by the operational station with the smallest id in the same power grid as x. If no operational station exists in that grid, return -1.

[2, x]: Station x goes offline (i.e., it becomes non-operational).

Return an array of integers representing the results of each query of type [1, x] in the order they appear.

Note: The power grid preserves its structure; an offline (non‑operational) node remains part of its grid and taking it offline does not alter connectivity.



Example 1:

Input: c = 5, connections = [[1,2],[2,3],[3,4],[4,5]], queries = [[1,3],[2,1],[1,1],[2,2],[1,2]]

Output: [3,2,3]

Explanation:



Initially, all stations {1, 2, 3, 4, 5} are online and form a single power grid.
Query [1,3]: Station 3 is online, so the maintenance check is resolved by station 3.
Query [2,1]: Station 1 goes offline. The remaining online stations are {2, 3, 4, 5}.
Query [1,1]: Station 1 is offline, so the check is resolved by the operational station with the smallest id among {2, 3, 4, 5}, which is station 2.
Query [2,2]: Station 2 goes offline. The remaining online stations are {3, 4, 5}.
Query [1,2]: Station 2 is offline, so the check is resolved by the operational station with the smallest id among {3, 4, 5}, which is station 3.
Example 2:

Input: c = 3, connections = [], queries = [[1,1],[2,1],[1,1]]

Output: [1,-1]

Explanation:

There are no connections, so each station is its own isolated grid.
Query [1,1]: Station 1 is online in its isolated grid, so the maintenance check is resolved by station 1.
Query [2,1]: Station 1 goes offline.
Query [1,1]: Station 1 is offline and there are no other stations in its grid, so the result is -1.


Constraints:

1 <= c <= 105
0 <= n == connections.length <= min(105, c * (c - 1) / 2)
connections[i].length == 2
1 <= ui, vi <= c
ui != vi
1 <= queries.length <= 2 * 105
queries[i].length == 2
queries[i][0] is either 1 or 2.
1 <= queries[i][1] <= c
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
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        vector<int> parent(c + 1, -1);
        vector<set<int>> grid(c + 1, set<int>());
        for (const vector<int>& conn : connections) {
            int u = find_parent(conn[0], parent);
            int v = find_parent(conn[1], parent);
            if (u == v) {
                continue;
            }
            parent[u] = v;
        }

        for (int i = 1; i <= c; i++) {
            grid[find_parent(i, parent)].insert(i);
        }

        vector<int> result;
        for (const vector<int>& q : queries) {
            int cur = q[1];
            int cur_parent = find_parent(cur, parent);
            if (q[0] == 2) {
                grid[cur_parent].erase(cur);
                continue;
            }

            if (grid[cur_parent].empty()) {
                result.push_back(-1);
            } else if (grid[cur_parent].find(cur) != grid[cur_parent].end()) {
                result.push_back(cur);
            } else {
                result.push_back(*grid[cur_parent].begin());
            }
        }
        return result;
    }
};
