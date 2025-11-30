/*
1761. Minimum Degree of a Connected Trio in a Graph
https://leetcode.com/problems/minimum-degree-of-a-connected-trio-in-a-graph/

You are given an undirected graph.
You are given an integer n which is the number of nodes in the graph and an array edges,
where each edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi.

A connected trio is a set of three nodes where there is an edge between every pair of them.
The degree of a connected trio is the number of edges where one endpoint is in the trio,
and the other is not.
Return the minimum degree of a connected trio in the graph,
or -1 if the graph has no connected trios.

Example 1:
Input: n = 6, edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
Output: 3
Explanation: There is exactly one trio, which is [1,2,3]. The edges that form its degree are bolded in the figure above.
Example 2:
Input: n = 7, edges = [[1,3],[4,1],[4,3],[2,5],[5,6],[6,7],[7,5],[2,6]]
Output: 0
Explanation: There are exactly three trios:
1) [1,4,3] with degree 0.
2) [2,5,6] with degree 2.
3) [5,6,7] with degree 2.

Constraints:
2 <= n <= 400
edges[i].length == 2
1 <= edges.length <= n * (n-1) / 2
1 <= ui, vi <= n
ui != vi
There are no repeated edges.
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
#include <climits>
#include <set>
#include <numeric>
#include <bitset>
using namespace std;

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> am(n + 1, vector<int>(n + 1));
        vector<int> cnt(n + 1);
        int res = INT_MAX;
        for (auto& e : edges) {
            am[min(e[0], e[1])][max(e[0], e[1])] = 1;
            ++cnt[e[0]];
            ++cnt[e[1]];
        }
        for (auto t1 = 1; t1 <= n; ++t1)
            for (auto t2 = t1 + 1; t2 <= n; ++t2)
                if (am[t1][t2])
                    for (auto t3 = t2 + 1; t3 <= n; ++t3)
                        if (am[t1][t3] && am[t2][t3])
                            res = min(res, cnt[t1] + cnt[t2] + cnt[t3] - 6);
        return res == INT_MAX ? -1 : res;
    }
};
