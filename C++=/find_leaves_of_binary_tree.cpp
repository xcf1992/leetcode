/*
366. Find Leaves of Binary Tree
https://leetcode.com/problems/find-leaves-of-binary-tree/

Given a binary tree, collect a tree's nodes as if you were doing this:
Collect and remove all leaves, repeat until the tree is empty.

Example:
Given binary tree
          1
         / \
        2   3
       / \
      4   5
Returns [4, 5, 3], [2], [1].
Explanation:
1. Removing the leaves [4, 5, 3] would result in this tree:

          1
         /
        2
2. Now removing the leaf [2] would result in this tree:

          1
3. Now removing the leaf [1] would result in the empty tree:

          []
Returns [4, 5, 3], [2], [1].
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
    int getHeight(TreeNode* root, unordered_map<int, vector<int>>& memo) {
        if (root == nullptr) {
            return -1;
        }

        int lh = getHeight(root -> left, memo);
        int rh = getHeight(root -> right, memo);
        int height = max(lh, rh) + 1;
        memo[height].push_back(root -> val);
        return height;
    }
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        unordered_map<int, vector<int>> memo;
        int maxHeight = getHeight(root, memo);
        vector<vector<int>> result(maxHeight + 1);
        for (auto& it : memo) {
            result[it.first] = it.second;
        }
        return result;
    }
};

class Solution1 {
private:
    vector<int> leaves;

    void traverse(TreeNode*& root) { // !!! use TreeNode*& here rather than TreeNode*
        if (root == nullptr) {
            return;
        }

        if (root -> left == nullptr and root -> right == nullptr) {
            leaves.push_back(root -> val);
            root = nullptr;
            return;
        }

        traverse(root -> left);
        traverse(root -> right);
    }

public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> result;
        while (root != nullptr) {
            traverse(root);
            result.push_back(leaves);
            leaves.clear();
        }
        return result;
    }
};