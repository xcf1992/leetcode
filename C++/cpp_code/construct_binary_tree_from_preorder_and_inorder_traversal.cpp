/*
105. Construct Binary Tree from Preorder and Inorder Traversal
https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:
    3
   / \
  9  20
    /  \
   15   7
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    TreeNode* createBinaryTree(vector<int>& inorder, int is, int ie, vector<int>& preorder, int ps, int pe) {
        if (is > ie or ps > pe) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(preorder[ps]);
        int i = 0;
        for (i = is; i != ie; i++) {
            if (inorder[i] == preorder[ps]) {
                break;
            }
        }

        root->left = createBinaryTree(inorder, is, i - 1, preorder, ps + 1, i - is + ps);
        root->right = createBinaryTree(inorder, i + 1, ie, preorder, i - is + ps + 1, pe);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (inorder.size() == 0) {
            return nullptr;
        }
        if (inorder.size() == 1) {
            return new TreeNode(inorder[0]);
        }
        return createBinaryTree(inorder, 0, inorder.size() - 1, preorder, 0, preorder.size() - 1);
    }
};
