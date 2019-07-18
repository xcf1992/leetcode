/*
106. Construct Binary Tree from Inorder and Postorder Traversal

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
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
    TreeNode* build(vector<int> &inorder, int is, int ie, vector<int> &postorder, int ps, int pe) {
        if (ps > pe) {
            return nullptr;
        }

        TreeNode *root = new TreeNode(postorder[pe]);
        int i = 0;
        for (i = is; i != ie; i++) {
            if (inorder[i] == postorder[pe]) {
                break;
            }
        }

        root -> left = build(inorder, is, i - 1, postorder, ps, i - is + ps - 1);
        root -> right = build(inorder, i + 1, ie, postorder, i - is + ps, pe - 1);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 0) {
            return nullptr;
        }
        if (inorder.size() == 1) {
            return new TreeNode(inorder[0]);
        }
        return build(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
};
