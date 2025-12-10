/*
513. Find Bottom Left Tree Value
https://leetcode.com/problems/find-bottom-left-tree-value/

Given a binary tree, find the leftmost value in the last row of the tree.

Example 1:
Input:
    2
   / \
  1   3

Output:
1

Example 2:
Input:
        1
       / \
      2   3
     /   / \
    4   5   6
       /
      7
Output:
7

Note:
You may assume the tree (i.e., the given root node) is not NULL.
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
    // dfs
private:
    void dfs(TreeNode* root, int height, int& longest, int& result) {
        if (root == nullptr) {
            return;
        }

        height += 1;
        if (height > longest) {
            longest = height;
            result = root->val;
        }
        dfs(root->left, height, longest, result);
        dfs(root->right, height, longest, result);
    }

public:
    int findBottomLeftValue(TreeNode* root) {
        int result = 0;
        int longest = 0;
        dfs(root, 0, longest, result);
        return result;
    }
};

class Solution {
    // bfs
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> row1;
        queue<TreeNode*> row2;
        int result = root->val;

        row1.push(root);

        while (!row1.empty() or !row2.empty()) {
            if (row2.empty()) {
                result = row1.front()->val;
                while (!row1.empty()) {
                    TreeNode* left_most = row1.front();
                    if (left_most->left != nullptr) {
                        row2.push(left_most->left);
                    }
                    if (left_most->right != nullptr) {
                        row2.push(left_most->right);
                    }
                    row1.pop();
                }
            } else {
                result = row2.front()->val;
                while (!row2.empty()) {
                    TreeNode* left_most = row2.front();
                    if (left_most->left != nullptr) {
                        row1.push(left_most->left);
                    }
                    if (left_most->right != nullptr) {
                        row1.push(left_most->right);
                    }
                    row2.pop();
                }
            }
        }

        return result;
    }
};