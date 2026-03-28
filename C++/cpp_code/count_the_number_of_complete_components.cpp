/*
https://leetcode.com/problems/count-the-number-of-complete-components/description/
2685. Count the Number of Complete Components

You are given an integer n. There is an undirected graph with n vertices, numbered from 0 to n - 1. You are given a 2D
integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting vertices ai and
bi.

Return the number of complete connected components of the graph.

A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of
the subgraph shares an edge with a vertex outside of the subgraph.

A connected component is said to be complete if there exists an edge between every pair of its vertices.



Example 1:



Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
Output: 3
Explanation: From the picture above, one can see that all of the components of this graph are complete.
Example 2:



Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
Output: 1
Explanation: The component containing vertices 0, 1, and 2 is complete since there is an edge between every pair of two
vertices. On the other hand, the component containing vertices 3, 4, and 5 is not complete since there is no edge
between vertices 4 and 5. Thus, the number of complete components in this graph is 1.


Constraints:

1 <= n <= 50
0 <= edges.length <= n * (n - 1) / 2
edges[i].length == 2
0 <= ai, bi <= n - 1
ai != bi
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
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<int> parent(n, -1);
        vector<int> node_cnt(n, 1);
        vector<int> edge_cnt(n, 0);
        for (vector<int>& e : edges) {
            int parent_u = find_parent(e[0], parent);
            int parent_v = find_parent(e[1], parent);
            if (parent_u != parent_v) {
                parent[parent_u] = parent_v;
                node_cnt[parent_v] += node_cnt[parent_u];
                edge_cnt[parent_v] += edge_cnt[parent_u];
            }

            // add the current new edge
            edge_cnt[find_parent(e[0], parent)] += 1;
        }

        int rst = 0;
        for (int i = 0; i < n; i++) {
            if (find_parent(i, parent) != i) {
                continue;
            }

            int k = node_cnt[i];
            if ((k - 1) * k / 2 == edge_cnt[i]) {
                rst += 1;
            }
        }
        return rst;
    }
};
/*
你的代码只是在数连通分量的个数，但题目要求的是数完全连通分量——即分量内每两个节点之间都有边。
比如三个节点连成一条链 0-1-2，这是一个连通分量，但不是完全的，因为缺少边 0-2。你的代码会把它算进去，但不应该。
你需要额外验证每个连通分量是否"完全"。一个有 k 个节点的完全分量恰好有 k*(k-1)/2
条边。所以找到每个分量的节点数和边数，检查一下就行：
 */