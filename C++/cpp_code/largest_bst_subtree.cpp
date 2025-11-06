/*
333. Largest BST Subtree
https://leetcode.com/problems/largest-bst-subtree/

Given a binary tree, find the largest subtree which is a Binary Search Tree (BST),
where largest means subtree with largest number of nodes in it.

Note:
A subtree must include all of its descendants.

Example:
Input: [10,5,15,1,8,null,7]
   10
   / \
  5  15
 / \   \
1   8   7
Output: 3
Explanation: The Largest BST Subtree in this case is the highlighted one.
             The return value is the subtree's size, which is 3.

Follow up:
Can you figure out ways to solve it with O(n) time complexity?
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
#include <stdio.h>
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    vector<int> count(TreeNode* root) {
        if (root == nullptr) {
            // cause when we do compare, we use current node value to compare with left Max, and right min
            // so we need to assign max to be INT_MIN and min to INT_MAX to make a leaf node always a BST
            return {INT_MAX, INT_MIN, 0};  // min, max, count
        }

        vector<int> leftSub = count(root->left);
        vector<int> rightSub = count(root->right);
        if (root->val > leftSub[1] and root->val < rightSub[0]) {
            // we cannot return {leftSub[0], rightSub[1], ...} here, because the leaf node case, we need return the
            // actual root val as return values
            return {min(root->val, leftSub[0]), max(root->val, rightSub[1]), leftSub[2] + 1 + rightSub[2]};
        }
        // current and further tree should be invalid BST
        // so we assign INT_MIN to min and INT_MAX to max, thus it is impossible to be less than INT_MIN
        // and bigger than INT_MAX
        return {INT_MIN, INT_MAX, max(leftSub[2], rightSub[2])};
    }

public:
    int largestBSTSubtree(TreeNode* root) {
        return count(root)[2];
    }
};