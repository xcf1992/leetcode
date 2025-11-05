/*
110. Balanced Binary Tree
https://leetcode.com/problems/balanced-binary-tree/

Given a binary tree, determine if it is height-balanced.
For this problem, a height-balanced binary tree is defined as:
a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example 1:
Given the following tree [3,9,20,null,null,15,7]:
    3
   / \
  9  20
    /  \
   15   7
Return true.

Example 2:
Given the following tree [1,2,2,3,3,null,null,4,4]:
       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
Return false.
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
    }
};

class Solution {
private:
    int getHeight(TreeNode *root, bool &result) {
        if (root == nullptr) {
            return 0;
        }
        if (root->left == nullptr and
        root->right == nullptr
        )
        {
            return 1;
        }

        int lh = getHeight(root->left, result);
        int rh = getHeight(root->right, result);
        if (abs(lh - rh) > 1) {
            result = false;
        }
        return max(lh, rh) + 1;
    }

public:
    bool isBalanced(TreeNode *root) {
        bool result = true;
        getHeight(root, result);
        return result;
    }
};