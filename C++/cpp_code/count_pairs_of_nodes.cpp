/*
1782. Count Pairs Of Nodes
https://leetcode.com/problems/count-pairs-of-nodes/

You are given an undirected graph represented by an integer n,
which is the number of nodes, and edges, where edges[i] = [ui, vi]
which indicates that there is an undirected edge between ui and vi.
You are also given an integer array queries.

The answer to the jth query is the number of pairs of nodes (a, b) that satisfy the following conditions:
a < b
cnt is strictly greater than queries[j],
where cnt is the number of edges incident to a or b.
Return an array answers such that answers.length == queries.length
and answers[j] is the answer of the jth query.

Note that there can be repeated edges.

Example 1:
Input: n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
Output: [6,5]
Explanation: The number of edges incident to at least one of each pair is shown above.
Example 2:
Input: n = 5, edges = [[1,5],[1,5],[3,4],[2,5],[1,3],[5,1],[2,3],[2,5]], queries = [1,2,3,4,5]
Output: [10,10,9,8,6]

Constraints:
2 <= n <= 2 * 104
1 <= edges.length <= 105
1 <= ui, vi <= n
ui != vi
1 <= queries.length <= 20
0 <= queries[j] < edges.length
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
using namespace std;

class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> cnt(n + 1), sorted_cnt(n + 1), res;
        vector<unordered_map<int, int>> shared(n + 1);
        for (auto& e : edges) {
            sorted_cnt[e[0]] = cnt[e[0]] = cnt[e[0]] + 1;
            sorted_cnt[e[1]] = cnt[e[1]] = cnt[e[1]] + 1;
            ++shared[min(e[0], e[1])][max(e[0], e[1])];
        }
        sort(begin(sorted_cnt), end(sorted_cnt));
        for (auto& q : queries) {
            res.push_back(0);
            for (int i = 1, j = n; i < j;)
                if (q < sorted_cnt[i] + sorted_cnt[j])
                    res.back() += (j--) - i;
                else
                    ++i;
            for (auto i = 1; i <= n; ++i)
                for (auto [j, sh_cnt] : shared[i])
                    if (q < cnt[i] + cnt[j] && q + sh_cnt >= cnt[i] + cnt[j])
                        --res.back();
        }
        return res;
    }
};