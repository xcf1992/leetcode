/*
https://leetcode.com/problems/count-nodes-with-the-highest-score/description/
2049. Count Nodes With the Highest Score

There is a binary tree rooted at 0 consisting of n nodes. The nodes are labeled from 0 to n - 1. You are given a
0-indexed integer array parents representing the tree, where parents[i] is the parent of node i. Since node 0 is the
root, parents[0] == -1.

Each node has a score. To find the score of a node, consider if the node and the edges connected to it were removed. The
tree would become one or more non-empty subtrees. The size of a subtree is the number of the nodes in it. The score of
the node is the product of the sizes of all those subtrees.

Return the number of nodes that have the highest score.



Example 1:

example-1
Input: parents = [-1,2,0,2,0]
Output: 3
Explanation:
- The score of node 0 is: 3 * 1 = 3
- The score of node 1 is: 4 = 4
- The score of node 2 is: 1 * 1 * 2 = 2
- The score of node 3 is: 4 = 4
- The score of node 4 is: 4 = 4
The highest score is 4, and three nodes (node 1, node 3, and node 4) have the highest score.
Example 2:

example-2
Input: parents = [-1,2,0]
Output: 2
Explanation:
- The score of node 0 is: 2 = 2
- The score of node 1 is: 2 = 2
- The score of node 2 is: 1 * 1 = 1
The highest score is 2, and two nodes (node 0 and node 1) have the highest score.


Constraints:

n == parents.length
2 <= n <= 105
parents[0] == -1
0 <= parents[i] <= n - 1 for i != 0
parents represents a valid binary tree.
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

class Solution {
private:
    void calc_subtree_cnt(int root, vector<vector<int>>& children, vector<vector<int>>& subtree_cnt) {
        for (int i = 0; i < children[root].size(); ++i) {
            int child = children[root][i];
            calc_subtree_cnt(child, children, subtree_cnt);
            subtree_cnt[root][i] = 1;
            for (int j = 0; j < subtree_cnt[child].size(); ++j) {
                subtree_cnt[root][i] += subtree_cnt[child][j];
            }
        }
    }

public:
    int countHighestScoreNodes(vector<int>& parents) {
        int n = parents.size();
        vector<vector<int>> children(n, vector<int>());
        for (int i = 1; i < n; ++i) {
            int parent = parents[i];
            children[parent].push_back(i);
        }

        vector<vector<int>> subtree_cnt(n, vector<int>(2, 0));
        calc_subtree_cnt(0, children, subtree_cnt);

        long long highest_score = 0;
        int rst = 0;
        for (int i = 0; i < n; i++) {
            long long score = 1;
            int left_cnt = n;
            for (int j = 0; j < subtree_cnt[i].size(); ++j) {
                if (subtree_cnt[i][j] == 0) {
                    continue;
                }
                score *= subtree_cnt[i][j];
                left_cnt -= subtree_cnt[i][j];
            }

            if (left_cnt - 1 != 0) {
                score *= (left_cnt - 1);
            }

            if (score > highest_score) {
                highest_score = score;
                rst = 1;
            } else if (score == highest_score) {
                rst += 1;
            }
        }
        return rst;
    }
};
