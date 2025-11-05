/*
112. Path Sum
https://leetcode.com/problems/path-sum/

Given a binary tree and a sum,
determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

Note:
A leaf is a node with no children.

Example:
Given the below binary tree and sum = 22,
      5
     / \
    4   8
   /   / \
  11  13  4
 /  \      \
7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == nullptr) {
            return false;
        }

        if (root->left == nullptr and
        root->right == nullptr
        )
        {
            return sum == root->val;
        }
        return hasPathSum(root->left, sum - root->val)
        or hasPathSum(root->right, sum - root->val);
    }
};