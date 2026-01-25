/*
https://leetcode.com/problems/find-the-level-of-tree-with-minimum-sum/description/
3157. Find the Level of Tree with Minimum Sum

Given the root of a binary tree root where each node has a value, return the level of the tree that has the minimum sum
of values among all the levels (in case of a tie, return the lowest level).

Note that the root of the tree is at level 1 and the level of any other node is its distance from the root + 1.



Example 1:

Input: root = [50,6,2,30,80,7]

Output: 2

Explanation:



Example 2:

Input: root = [36,17,10,null,null,24]

Output: 3

Explanation:



Example 3:

Input: root = [5,null,5,null,5]

Output: 1

Explanation:





Constraints:

The number of nodes in the tree is in the range [1, 105].
1 <= Node.val <= 109
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
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {
    }
};

class Solution {
public:
    int minimumLevel(TreeNode* root) {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
            return 1;
        }

        queue<TreeNode*> bfs;
        bfs.push(root);
        int cur_lvl = 1;
        long long min_sum = LONG_LONG_MAX;
        int rst = 1;
        while (!bfs.empty()) {
            int cur_size = bfs.size();
            long long cur_sum = 0;
            for (int i = 0; i < cur_size; i++) {
                TreeNode* cur = bfs.front();
                bfs.pop();

                cur_sum += cur->val;
                if (cur->left != nullptr) {
                    bfs.push(cur->left);
                }
                if (cur->right != nullptr) {
                    bfs.push(cur->right);
                }
            }

            if (cur_sum < min_sum) {
                min_sum = cur_sum;
                rst = cur_lvl;
            }
            cur_lvl += 1;
        }
        return rst;
    }
};