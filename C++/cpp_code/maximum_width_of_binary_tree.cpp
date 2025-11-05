/*
662. Maximum Width of Binary Tree
https://leetcode.com/problems/maximum-width-of-binary-tree/

Given a binary tree, write a function to get the maximum width of the given tree.
The width of a tree is the maximum width among all levels.
The binary tree has the same structure as a full binary tree,
but some nodes are null.

The width of one level is defined as the length between the end-nodes
(the leftmost and right most non-null nodes in the level,
where the null nodes between the end-nodes are also counted into the length calculation.

Example 1:
Input:
           1
         /   \
        3     2
       / \     \
      5   3     9
Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).

Example 2:
Input:
          1
         /
        3
       / \
      5   3
Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).

Example 3:
Input:
          1
         / \
        3   2
       /
      5
Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).

Example 4:
Input:
          1
         / \
        3   2
       /     \
      5       9
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).

Note:
Answer will in the range of 32-bit signed integer.
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
#include <stdio.h>
#include <map>
#include "extra_data_types.hpp"
using namespace std;

class Solution1 {
private:
    void dfs(int &result, unordered_map<int, int> &index, int height, int pos, TreeNode *root) {
        if (root == nullptr) {
            return;
        }

        if (index.find(height) == index.end()) {
            index[height] = pos;
        } else {
            result = max(result, pos - index[height] + 1);
        }

        dfs(result, index, height + 1, pos * 2, root->left);
        dfs(result, index, height + 1, pos * 2 + 1, root->right);
    }

public:
    int widthOfBinaryTree(TreeNode *root) {
        int result = 0;
        unordered_map<int, int> index;
        dfs(result, index, 0, 0, root);
        return result;
    }
};

class Solution {
public:
    int widthOfBinaryTree(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        int result = 1;
        queue<pair<int, TreeNode *> > row;
        row.push({0, root});
        while (!row.empty()) {
            int left = INT_MAX;
            int right = INT_MIN;
            int curSize = row.size();
            for (int i = 0; i < curSize; ++i) {
                int pos = row.front().first;
                TreeNode *node = row.front().second;
                row.pop();

                left = min(left, pos);
                right = max(right, pos);
                if (node->left) {
                    row.push({pos * 2, node->left});
                }
                if (node->right) {
                    row.push({pos * 2 + 1, node->right});
                }
            }
            if (left <= right) {
                result = max(result, right - left + 1);
            }
        }
        return result;
    }
};