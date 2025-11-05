/*
298. Binary Tree Longest Consecutive Sequence
https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/

Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections.
The longest consecutive path need to be from parent to child (cannot be the reverse).

Example 1:
Input:
   1
    \
     3
    / \
   2   4
        \
         5
Output: 3
Explanation: Longest consecutive sequence path is 3-4-5, so return 3.

Example 2:
Input:
   2
    \
     3
    /
   2
  /
 1
Output: 2
Explanation: Longest consecutive sequence path is 2-3, not 3-2-1, so return 2.
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

class Solution {
private:
    void traverse(TreeNode *root, TreeNode *pre, int &result, int length) {
        if (root == nullptr) {
            return;
        }
        if (pre != nullptr and
        root->val != 1 + pre->val
        )
        {
            length = 0;
        }

        length += 1;
        result = max(result, length);
        traverse(root->left, root, result, length);
        traverse(root->right, root, result, length);
    }

public:
    int longestConsecutive(TreeNode *root) {
        int result = 0;
        traverse(root, nullptr, result, 0);
        return result;
    }
};

class Solution2 {
private:
    int traverse(TreeNode *root, int &result) {
        if (root == nullptr) {
            return 0;
        }

        int l1 = traverse(root->left, result);
        int l2 = traverse(root->right, result);

        if (root->left != nullptr and
        root->left->val != root->val + 1
        )
        {
            l1 = 0;
        }
        if (root->right != nullptr and
        root->right->val != root->val + 1
        )
        {
            l2 = 0;
        }
        int l = max(l1, l2) + 1;
        result = max(result, l);
        return l;
    }

public:
    int longestConsecutive(TreeNode *root) {
        int result = 0;
        traverse(root, result);
        return result;
    }
};

class Solution1 {
private:
    int getLength(TreeNode *root, int preVal) {
        if (root == nullptr) {
            return 0;
        }

        if (root->val == preVal + 1) {
            return max(getLength(root->left, root->val), getLength(root->right, root->val)) + 1;
        }
        return 0;
    }

public:
    int longestConsecutive(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        int l1 = getLength(root->left, root->val) + 1;
        int l2 = getLength(root->right, root->val) + 1;
        int l = max(longestConsecutive(root->left), longestConsecutive(root->right));
        return max(l, max(l1, l2));
    }
};