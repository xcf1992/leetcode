/*
124. Binary Tree Maximum Path Sum
https://leetcode.com/problems/binary-tree-maximum-path-sum/

Given a non-empty binary tree,
find the maximum path sum.

For this problem,
a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child
connections. The path must contain at least one node and does not need to go through the root.

Example 1:
Input: [1,2,3]
       1
      / \
     2   3
Output: 6

Example 2:
Input: [-10,9,20,null,null,15,7]
   -10
   / \
  9  20
    /  \
   15   7
Output: 42
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
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
private:
    int get_sum(TreeNode* root, int& result) {
        if (root == nullptr) {
            return 0;
        }

        int left_sum = max(0, get_sum(root->left, result));
        int right_sum = max(0, get_sum(root->right, result));
        int sum = left_sum + right_sum + root->val;
        result = max(result, sum);
        return max(left_sum, right_sum) + root->val;
    }

public:
    int maxPathSum(TreeNode* root) {
        int result = INT_MIN;
        get_sum(root, result);
        return result;
    }
};