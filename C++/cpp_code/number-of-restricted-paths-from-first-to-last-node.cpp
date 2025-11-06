/*
1786. Number of Restricted Paths From First to Last Node
https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/

There is an undirected weighted connected graph.
You are given a positive integer n
which denotes that the graph has n nodes labeled from 1 to n,
and an array edges where each edges[i] = [ui, vi, weighti]
denotes that there is an edge between nodes ui and vi with weight equal to weighti.

A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk]
such that z0 = start and zk = end and there is an edge between zi and zi+1 where 0 <= i <= k-1.

The distance of a path is the sum of the weights on the edges of the path.
Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x.
A restricted path is a path that also satisfies that distanceToLastNode(zi) > distanceToLastNode(zi+1)
where 0 <= i <= k-1.

Return the number of restricted paths from node 1 to node n.
Since that number may be too large, return it modulo 109 + 7.

Example 1:
Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
Output: 3
Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three
restricted paths are: 1) 1 --> 2 --> 5 2) 1 --> 2 --> 3 --> 5 3) 1 --> 3 --> 5 Example 2: Input: n = 7, edges =
[[1,3,1],[4,1,2],[7,3,4],[2,5,3],[5,6,1],[6,7,2],[7,5,3],[2,6,4]] Output: 1 Explanation: Each circle contains the node
number in black and its distanceToLastNode value in blue. The only restricted path is 1 --> 3 --> 7.

Constraints:
1 <= n <= 2 * 104
n - 1 <= edges.length <= 4 * 104
edges[i].length == 3
1 <= ui, vi <= n
ui != vi
1 <= weighti <= 105
There is at most one edge between any two nodes.
There is at least one path between any two nodes.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;
/*
We use Dijkstra to calculate shortest distance paths from last node n to any other nodes x,
the result is distanceToLastNode(x),
where x in 1..n.
Complexity: O(E * logV) = O(M logN),
where M is number of edges, N is number of nodes.

In the restricted path,
[z0, z1, z2, ..., zk], node zi always stand before node z(i+1)
because distanceToLastNode(zi) > distanceToLastNode(zi+1),
mean while dfs do calculate number of paths,
a current node never comeback to visited nodes,
so we don't need to use visited array to check visited nodes.
Then our dfs(src) function only depends on one param src,
we can use memory cache to cache precomputed results of dfs function,
so the time complexity can be deduced to be O(E).

Complexity:
Time: O(M * logN), where M is number of edges, N is number of nodes.
Space: O(M + N)
*/
class Solution {
private:
    // Declaring variables gloabally so that we don't need to pass every time in function and we can directly access in
    // dfs function
    unordered_map<int, vector<pair<int, int>>> m;
    vector<int> dist;
    vector<int> dp;

    int N;
    int MOD = 1000000007;

    int dfs(int u) {
        if (dp[u] != -1)
            return dp[u];

        if (u == N)
            return 1;

        int ans = 0;
        for (auto p : m[u]) {
            int v = p.first;
            if (dist[v] < dist[u])
                ans = (ans + dfs(v)) % MOD;
        }
        return dp[u] = ans;
    }

public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        vector<int> vis(n + 1, 0);
        dist.resize(n + 1, INT_MAX);
        dp.resize(n + 1, -1);
        dist[0] = 0;
        N = n;
        for (auto i : edges) {
            m[i[0]].push_back({i[1], i[2]});
            m[i[1]].push_back({i[0], i[2]});
        }

        set<pair<int, int>> q;
        q.insert({0, n});
        dist[n] = 0;
        while (!q.empty()) {
            int u = q.begin()->second;
            q.erase(q.begin());

            vis[u] = 1;
            for (auto p : m[u]) {
                int v = p.first;
                int w = p.second;
                if (!vis[v]) {
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        q.insert({dist[v], v});
                    }
                }
            }
        }
        return dfs(1);
    }
};
