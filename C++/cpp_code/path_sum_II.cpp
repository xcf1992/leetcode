/*
113. Path Sum II
https://leetcode.com/problems/path-sum-ii/

Given a binary tree and a sum,
find all root-to-leaf paths where each path's sum equals the given sum.
Note: A leaf is a node with no children.

Example:
Given the below binary tree and sum = 22,
      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1
Return:
[
   [5,4,11,2],
   [5,8,4,5]
]
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
    void dfs(TreeNode* root, vector<int>& path, vector<vector<int>>& result, int sum) {
        if (root == nullptr) {
            return;
        }

        path.push_back(root->val);
        if (root->left == nullptr and root->right == nullptr and sum == root->val) {
            result.push_back(path);
        }

        dfs(root->left, path, result, sum - root->val);
        dfs(root->right, path, result, sum - root->val);
        path.pop_back();  // when return to upper level pop current num
    }

public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> result;
        vector<int> path;
        dfs(root, path, result, sum);
        return result;
    }
};