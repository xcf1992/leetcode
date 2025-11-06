/*
538. Convert BST to Greater Tree

Given a Binary Search Tree (BST),
convert it to a Greater Tree such that every key of the original BST is changed to
the original key plus sum of all keys greater than the original key in BST.

Example:

Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13
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
    void traverse(TreeNode* root, TreeNode*& prev) {
        if (root == nullptr) {
            return;
        }

        traverse(root->right, prev);
        if (prev != nullptr) {
            root->val += prev->val;
        }
        prev = root;
        traverse(root->left, prev);
    }

public:
    TreeNode* convertBST(TreeNode* root) {
        TreeNode* prev = nullptr;
        traverse(root, prev);
        return root;
    }
};