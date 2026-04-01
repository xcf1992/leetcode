/*
https://leetcode.com/problems/choose-edges-to-maximize-score-in-a-tree/description/
2378. Choose Edges to Maximize Score in a Tree
You are given a weighted tree consisting of n nodes numbered from 0 to n - 1.

The tree is rooted at node 0 and represented with a 2D array edges of size n where edges[i] = [pari, weighti] indicates
that node pari is the parent of node i, and the edge between them has a weight equal to weighti. Since the root does not
have a parent, you have edges[0] = [-1, -1].

Choose some edges from the tree such that no two chosen edges are adjacent and the sum of the weights of the chosen
edges is maximized.

Return the maximum sum of the chosen edges.

Note:

You are allowed to not choose any edges in the tree, the sum of weights in this case will be 0.
Two edges Edge1 and Edge2 in the tree are adjacent if they have a common node.
In other words, they are adjacent if Edge1 connects nodes a and b and Edge2 connects nodes b and c.


Example 1:


Input: edges = [[-1,-1],[0,5],[0,10],[2,6],[2,4]]
Output: 11
Explanation: The above diagram shows the edges that we have to choose colored in red.
The total score is 5 + 6 = 11.
It can be shown that no better score can be obtained.
Example 2:


Input: edges = [[-1,-1],[0,5],[0,-6],[0,7]]
Output: 7
Explanation: We choose the edge with weight 7.
Note that we cannot choose more than one edge because all edges are adjacent to each other.


Constraints:

n == edges.length
1 <= n <= 105
edges[i].length == 2
par0 == weight0 == -1
0 <= pari <= n - 1 for all i >= 1.
pari != i
-106 <= weighti <= 106 for all i >= 1.
edges represents a valid tree.
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
private:
    vector<vector<pair<int, int>>> adj_;

    // returns {not_picked, picked}
    // not_picked: max score when edge u-parent is NOT selected
    // picked:     max score when edge u-parent IS selected (no edge u-child allowed)
    pair<long long, long long> dfs(int cur) {
        long long sum_not = 0;    // sum of dp[child][0] for all children
        long long best_gain = 0;  // best gain from picking one cur-child edge
        for (int i = 0; i < adj_[cur].size(); ++i) {
            int child = adj_[cur][i].first;
            int cur_to_child_w = adj_[cur][i].second;
            auto [child_not, child_pick] = dfs(child);

            sum_not += child_not;
            // gain of picking edge u-child instead of not picking it
            long long gain = child_pick + cur_to_child_w - child_not;
            if (gain > best_gain) {
                best_gain = gain;
            }
        }
        // not_picked: can pick at most one u-child edge
        long long not_picked = sum_not + best_gain;

        // picked: edge u-parent selected, so no u-child edge allowed
        long long picked = sum_not;

        return make_pair(not_picked, picked);
    }

public:
    long long maxScore(vector<vector<int>>& edges) {
        int n = edges.size();
        adj_.resize(n, vector<pair<int, int>>());
        for (int i = 1; i < n; i++) {
            int parent = edges[i][0];
            int weight = edges[i][1];
            adj_[parent].push_back({i, weight});
        }
        return dfs(0).first;
    }
};
/*
关键思路：
不能选相邻边 → 共享节点的边不能同时选 → 对于每个节点，最多只能选它的一条关联边。
DP 定义（对每个节点 u）：

not_picked：不选 u→parent 这条边时，u 的子树能获得的最大分数
picked：选了 u→parent 这条边时，u 的子树能获得的最大分数

转移：

picked = sum(child_not)：选了 u→parent，u 不能再和任何 child 连边，所以所有 child 都只能走 not_picked
not_picked = sum(child_not) + max(0, max_gain)：不选 u→parent，可以选至多一条 u→child 边。选 child_i 的收益是
child_i_picked + weight_i - child_i_not，取最大且为正的那个

答案： dfs(0).first，根节点没有 parent 边，取 not_picked。
时间复杂度： O(n)，每个节点访问一次，每条边处理一次。
空间复杂度： O(n)，邻接表 + 递归栈。为什么 long long picked = sum_not; 如果 u-parent 被选上了, 应该还要加上 u-parent 的
weight?7:17
PM阐明了边权由父节点而非子节点负责计算的设计原理。阐明了边权由父节点而非子节点负责计算的设计原理。好问题。这是一个职责划分的设计选择：边的
weight 不由 child 加，而是由 parent 那一层加。 看这行代码： cpplong long gain = child_picked + w - child_not;
```

`w`（也就是 u→child 边的 weight）是在 **u 这一层**计算 gain 时加上去的，而不是 child 返回时自己加的。

所以整个设计是：`picked` 和 `not_picked` 都只描述**子树内部**的贡献，不包含连向 parent 的那条边的 weight。边的 weight
永远由**上面那层**来加。

具体走一遍：
```
    parent
      |  (weight=5)
      u
     / \
   c1   c2

dfs(u) 返回 picked = sum_not，意思是"如果 u→parent 被选了，u 子树内部能贡献多少"
在 dfs(parent) 里，parent 决定要不要选 parent→u 这条边，计算：gain = u_picked + 5 - u_not

weight=5 是在 parent 层加的，不是 u 层加的。这样避免了重复计算，逻辑也更清晰。
 */