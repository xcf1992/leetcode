/*
https://leetcode.com/problems/shortest-path-in-a-weighted-tree/description/
3515. Shortest Path in a Weighted Tree

You are given an integer n and an undirected, weighted tree rooted at node 1 with n nodes numbered from 1 to n. This is
represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an undirected edge from node ui
to vi with weight wi.

You are also given a 2D integer array queries of length q, where each queries[i] is either:

[1, u, v, w'] – Update the weight of the edge between nodes u and v to w', where (u, v) is guaranteed to be an edge
present in edges. [2, x] – Compute the shortest path distance from the root node 1 to node x. Return an integer array
answer, where answer[i] is the shortest path distance from node 1 to x for the ith query of [2, x].



Example 1:

Input: n = 2, edges = [[1,2,7]], queries = [[2,2],[1,1,2,4],[2,2]]

Output: [7,4]

Explanation:



Query [2,2]: The shortest path from root node 1 to node 2 is 7.
Query [1,1,2,4]: The weight of edge (1,2) changes from 7 to 4.
Query [2,2]: The shortest path from root node 1 to node 2 is 4.
Example 2:

Input: n = 3, edges = [[1,2,2],[1,3,4]], queries = [[2,1],[2,3],[1,1,3,7],[2,2],[2,3]]

Output: [0,4,2,7]

Explanation:



Query [2,1]: The shortest path from root node 1 to node 1 is 0.
Query [2,3]: The shortest path from root node 1 to node 3 is 4.
Query [1,1,3,7]: The weight of edge (1,3) changes from 4 to 7.
Query [2,2]: The shortest path from root node 1 to node 2 is 2.
Query [2,3]: The shortest path from root node 1 to node 3 is 7.
Example 3:

Input: n = 4, edges = [[1,2,2],[2,3,1],[3,4,5]], queries = [[2,4],[2,3],[1,2,3,3],[2,2],[2,3]]

Output: [8,3,2,5]

Explanation:



Query [2,4]: The shortest path from root node 1 to node 4 consists of edges (1,2), (2,3), and (3,4) with weights 2 + 1 +
5 = 8. Query [2,3]: The shortest path from root node 1 to node 3 consists of edges (1,2) and (2,3) with weights 2 + 1
= 3. Query [1,2,3,3]: The weight of edge (2,3) changes from 1 to 3. Query [2,2]: The shortest path from root node 1 to
node 2 is 2. Query [2,3]: The shortest path from root node 1 to node 3 consists of edges (1,2) and (2,3) with updated
weights 2 + 3 = 5.


Constraints:

1 <= n <= 105
edges.length == n - 1
edges[i] == [ui, vi, wi]
1 <= ui, vi <= n
1 <= wi <= 104
The input is generated such that edges represents a valid tree.
1 <= queries.length == q <= 105
queries[i].length == 2 or 4
queries[i] == [1, u, v, w'] or,
queries[i] == [2, x]
1 <= u, v, x <= n
(u, v) is always an edge from edges.
1 <= w' <= 104
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Fenwick {
    int n;
    vector<long long> BIT;
    Fenwick(int n) : n(n), BIT(n + 1, 0) {
    }
    void update(int i, long long delta) {
        for (; i <= n; i += i & -i)
            BIT[i] += delta;
    }
    long long query(int i) {
        long long sum = 0;
        for (; i; i -= i & -i)
            sum += BIT[i];
        return sum;
    }
};

struct Tree {
    int N, root = 1;
    vector<vector<pair<int, int>>> adj;
    vector<int> tin, tout, par, depth;
    vector<long long> rootD;
    int timer = 0;
    Tree(int _N) {
        N = _N;
        adj.resize(N + 1);
        tin.resize(N + 1);
        tout.resize(N + 1);
        par.resize(N + 1);
        depth.resize(N + 1);
        rootD.resize(N + 1);
    }
    void add_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    void init(int rt = 1) {
        root = rt;
        timer = 0;
        function<void(int, int, long long)> dfs = [&](int u, int p, long long dist) {
            par[u] = p;
            rootD[u] = dist;
            tin[u] = ++timer;
            depth[u] = depth[p] + 1;
            for (auto& [v, w] : adj[u])
                if (v != p)
                    dfs(v, u, dist + w);
            tout[u] = timer;
        };
        dfs(root, 0, 0);
        // DFS Preprocessing for calcualting parent , rootD , and tin and tout times
    }
};

class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        Tree tree(n);
        vector<int> ans;
        for (auto& e : edges)
            tree.add_edge(e[0], e[1], e[2]);
        tree.init(1);
        Fenwick F(tree.timer);
        vector<int> up(n + 1, 0);
        for (int i = 2; i <= n; ++i)
            for (auto& [u, w] : tree.adj[i])
                if (u == tree.par[i])
                    up[i] = w;
        for (auto& q : queries) {
            if (q[0] == 1) {
                int u = q[1], v = q[2], c = v;
                if (tree.par[u] == v)
                    c = u;  // c = child
                // Range Update in Fenwick Tree , the change in weight
                // delta = q[3] - up[c]
                // we add this value at tin[child]
                // and subtract at tout[child] + 1
                F.update(tree.tin[c], q[3] - up[c]);
                F.update(tree.tout[c] + 1, up[c] - q[3]);
                up[c] = q[3];
            } else
                ans.push_back((int)(tree.rootD[q[1]] + F.query(tree.tin[q[1]])));
            //                             intial weight   + changes done in weights
        }
        return ans;
    }
};