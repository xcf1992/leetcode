/*
98. Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.


Example 1:

    2
   / \
  1   3

Input: [2,1,3]
Output: true
Example 2:

    5
   / \
  1   4
     / \
    3   6

Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include "extra_data_types.hpp"
using namespace std;

class Solution { // use stack
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stk;
        long long curMin = (long long)INT_MIN - 1;
        while (!stk.empty() or root != nullptr) {
            while (root != nullptr) {
                stk.push(root);
                root = root -> left;
            }
            root = stk.top();
            stk.pop();
            /*
            * If next element in inorder traversal
            * is smaller than the previous one
            * that's not BST.
           */
            if (root -> val <= curMin) {
                return false;
            }
            curMin = root -> val;
            root = root -> right;
        }
        return true;
    }
};

class Solution1 { // use lower bound and upper bound
private:
    bool validate(TreeNode *root, long long minVal, long long maxVal) {
        if (root == NULL) {
            return true;
        }

        if (root -> val >= maxVal or root -> val <= minVal) {
            return false;
        }
        return validate(root -> right, root -> val, maxVal) and validate(root -> left, minVal, root -> val);
    }
public:
    bool isValidBST(TreeNode *root) {
        long long minVal = (long long)INT_MIN - 1;
        long long maxVal = (long long)INT_MAX + 1;
        return validate(root, minVal, maxVal);
    }
};
