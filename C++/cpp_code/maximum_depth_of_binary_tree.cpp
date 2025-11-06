/*
104. Maximum Depth of Binary Tree
https://leetcode.com/problems/maximum-depth-of-binary-tree/

Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Note:
A leaf is a node with no children.

Example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its depth = 3.
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
private:
    void traverse(TreeNode* root, int curDep, int& result) {
        if (root == nullptr) {
            return;
        }

        curDep += 1;
        result = max(result, curDep);
        traverse(root->left, curDep, result);
        traverse(root->right, curDep, result);
    }

public:
    int maxDepth(TreeNode* root) {
        int result = 0;
        traverse(root, 0, result);
        return result;
    }
};