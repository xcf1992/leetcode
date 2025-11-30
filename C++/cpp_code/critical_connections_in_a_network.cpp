/*
1192. Critical Connections in a Network
https://leetcode.com/problems/critical-connections-in-a-network/

There are n servers numbered from 0 to n-1 connected by undirected server-to-server connections forming a network
where connections[i] = [a, b] represents a connection between servers a and b.
Any server can reach any other server directly or indirectly through the network.

A critical connection is a connection that,
if removed, will make some server unable to reach some other server.
Return all critical connections in the network in any order.

Example 1:
Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.

Constraints:
1 <= n <= 10^5
n-1 <= connections.length <= 10^5
connections[i][0] != connections[i][1]
There are no repeated connections.
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
using namespace std;
/*
https://www.geeksforgeeks.org/bridge-in-a-graph/
https://cp-algorithms.com/graph/bridge-searching.html
*/
class Solution {
private:
    int time = 0;

    void dfs(int cur, vector<bool>& visited, vector<int>& disc, vector<int>& low, vector<int>& parent,
             vector<vector<int>>& graph, vector<vector<int>>& result) {
        visited[cur] = true;
        time += 1;
        disc[cur] = low[cur] = time;
        for (int nxt : graph[cur]) {
            if (!visited[nxt]) {
                parent[nxt] = cur;
                dfs(nxt, visited, disc, low, parent, graph, result);
                low[cur] = min(low[cur], low[nxt]);
                if (low[nxt] > disc[cur]) {
                    result.push_back({cur, nxt});
                }
            } else if (nxt != parent[cur]) {
                low[cur] = min(low[cur], disc[nxt]);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> graph(n, vector<int>());
        for (vector<int>& con : connections) {
            graph[con[0]].push_back(con[1]);
            graph[con[1]].push_back(con[0]);
        }

        vector<bool> visited(n, false);
        vector<int> disc(n, 0), low(n, 0), parent(n, -1);
        vector<vector<int>> result;
        for (int i = 0; i < n; ++i)
            if (!visited[i]) {
                dfs(i, visited, disc, low, parent, graph, result);
            }
        return result;
    }
};