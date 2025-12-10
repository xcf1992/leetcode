/*
102. Binary Tree Level Order Traversal
https://leetcode.com/problems/binary-tree-level-order-traversal/

Given a binary tree, return the level order traversal of its nodes' values.
(ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        queue<TreeNode*> bfs;
        bfs.push(root);
        vector<vector<int>> result;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            vector<int> row;
            for (int i = 0; i < curSize; ++i) {
                TreeNode* node = bfs.front();
                bfs.pop();

                row.push_back(node->val);
                if (node->left) {
                    bfs.push(node->left);
                }
                if (node->right) {
                    bfs.push(node->right);
                }
            }
            result.push_back(row);
        }
        return result;
    }
};