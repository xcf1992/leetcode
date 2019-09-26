/*
971. Flip Binary Tree To Match Preorder Traversal
https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/

Given a binary tree with N nodes, each node has a different value from {1, ..., N}.

A node in this binary tree can be flipped by swapping the left child and the right child of that node.

Consider the sequence of N values reported by a preorder traversal starting from the root.
Call such a sequence of N values the voyage of the tree.

(Recall that a preorder traversal of a node means we report the current node's value,
then preorder-traverse the left child,
then preorder-traverse the right child.)

Our goal is to flip the least number of nodes in the tree so that the voyage of the tree matches the voyage we are given.

If we can do so, then return a list of the values of all nodes flipped.
You may return the answer in any order.

If we cannot do so, then return the list [-1].

Example 1:
  1
 /
2
Input: root = [1,2], voyage = [2,1]
Output: [-1]

Example 2:
    1
  /   \
2     3
Input: root = [1,2,3], voyage = [1,3,2]
Output: [1]

Example 3:
    1
  /   \
2     3
Input: root = [1,2,3], voyage = [1,2,3]
Output: []


Note:
1 <= N <= 100
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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution { // iterative with stace
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        vector<int> result;
        stack<TreeNode*> stk;
        stk.push(root);
        int pos = 0;
        while (!stk.empty()) {
            TreeNode* cur = stk.top();
            stk.pop();
            if (cur == nullptr) {
                continue;
            }

            if (cur -> val != voyage[pos]) {
                return vector<int>{-1};
            }

            pos += 1;
            if (cur -> right != nullptr and cur -> right -> val == voyage[pos]) {
                if (cur -> left != nullptr) {
                    result.push_back(cur -> val);
                }
                stk.push(cur -> left);
                stk.push(cur -> right);
            }
            else {
                stk.push(cur -> right);
                stk.push(cur -> left);
            }
        }
        return result;
    }
};

class Solution1 { // recursive
private:
    bool traversal(TreeNode* root, vector<int>& voyage, vector<int>& result, int& cur) {
        if (root == nullptr) {
            return true;
        }

        if (root -> val != voyage[cur]) {
            return false;
        }

        cur += 1;
        if (root -> left != nullptr and root -> left -> val != voyage[cur]) {
            result.push_back(root -> val);
            return traversal(root -> right, voyage, result, cur) and traversal(root -> left, voyage, result, cur);
        }
        return traversal(root -> left, voyage, result, cur) and traversal(root -> right, voyage, result, cur);
    }
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        vector<int> result;
        int cur = 0;
        return traversal(root, voyage, result, cur) ? result : vector<int>{-1};
    }
};

class Solution2 {
private:
    bool traversal(TreeNode* root, vector<int>& voyage, vector<int>& result, int& cur) {
        if (root == nullptr) {
            return true;
        }

        if (root -> val != voyage[cur]) {
            return false;
        }

        cur += 1;
        if (cur == voyage.size()) {
            return true;
        }

        if (root -> left != nullptr) {
            if (root -> left -> val != voyage[cur]) {
                if (root -> right == nullptr or root -> right -> val != voyage[cur]) {
                    return false;
                }
                swap(root -> left, root -> right);
                result.push_back(root -> val);
            }
            if (!traversal(root -> left, voyage, result, cur)) {
                return false;
            }
        }
        return traversal(root -> right, voyage, result, cur);
    }
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        vector<int> result;
        int cur = 0;
        if (!traversal(root, voyage, result, cur)) {
            return {-1};
        }
        return result;
    }
};
