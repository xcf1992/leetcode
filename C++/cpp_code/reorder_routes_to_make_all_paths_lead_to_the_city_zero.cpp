/*
1466. Reorder Routes to Make All Paths Lead to the City Zero
https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/

There are n cities numbered from 0 to n-1 and n-1 roads
such that there is only one way to travel between two different cities (this network form a tree).
Last year, The ministry of transport decided to orient the roads in one direction because they are too narrow.

Roads are represented by connections where connections[i] = [a, b] represents a road from city a to b.
This year, there will be a big event in the capital (city 0), and many people want to travel to this city.

Your task consists of reorienting some roads such that each city can visit the city 0.
Return the minimum number of edges changed.
It's guaranteed that each city can reach the city 0 after reorder.

Example 1:
Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
Output: 3
Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).

Example 2:
Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
Output: 2
Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).

Example 3:
Input: n = 3, connections = [[1,0],[2,0]]
Output: 0

Constraints:
2 <= n <= 5 * 10^4
connections.length == n-1
connections[i].length == 2
0 <= connections[i][0], connections[i][1] <= n-1
connections[i][0] != connections[i][1]
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
#include <map>
#include <climits>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int dfs(vector<vector<int>>& al, vector<bool>& visited, int from) {
        auto change = 0;
        visited[from] = true;
        for (auto to : al[from])
            if (!visited[abs(to)])
                change += dfs(al, visited, abs(to)) + (to > 0);
        return change;
    }

public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>> al(n);
        for (auto& c : connections) {
            al[c[0]].push_back(c[1]);
            al[c[1]].push_back(-c[0]);
        }
        return dfs(al, vector<bool>(n) = {}, 0);
    }
};

class Solution1 {  // TLE
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>> canReach(n, vector<int>(n, 0));
        for (vector<int>& con : connections) {
            canReach[con[0]][con[1]] = 1;
            canReach[con[1]][con[0]] = -1;
        }

        queue<int> bfs;
        bfs.push(0);
        vector<bool> visited(n, false);
        visited[0] = true;
        int result = 0;
        while (!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();

            for (int i = 0; i < n; ++i)
                if (i != cur and !visited[i]) {
                    if (canReach[cur][i] == 0) {
                        continue;
                    }

                    if (canReach[cur][i] == 1) {
                        result += 1;
                    }
                    bfs.push(i);
                    visited[i] = true;
                }
        }
        return result;
    }
};
