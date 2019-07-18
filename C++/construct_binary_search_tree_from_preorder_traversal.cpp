/*
 1008. Construct Binary Search Tree from Preorder Traversal

 Return the root node of a binary search tree that matches the given preorder traversal.

 (Recall that a binary search tree is a binary tree where for every node,
 any descendant of node.left has a value < node.val,
 and any descendant of node.right has a value > node.val.
 Also recall that a preorder traversal displays the value of the node first,
 then traverses node.left,
 then traverses node.right.)

 Example 1:

 Input: [8,5,1,7,10,12]
 Output: [8,5,10,1,7,null,12]

 Note:

 1 <= preorder.length <= 100
 The values of preorder are distinct.
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
#include <set>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution { // iterative same process as 255. Verify Preorder Sequence in Binary Search Tree
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if (preorder.empty()) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> stk;
        stk.push(root);
        for (int i = 1; i < preorder.size(); ++i) {
            TreeNode* node = new TreeNode(preorder[i]);
            if (!stk.empty() and stk.top() -> val > node -> val) {
                stk.top() -> left = node;
            }
            else {
                TreeNode* parent = nullptr;
                while (!stk.empty() and stk.top() -> val < node -> val) {
                    parent = stk.top();
                    stk.pop();
                }
                parent -> right = node;
            }
            stk.push(node);
        }
        return root;
    }
};

class Solution2 { // recursive only loop once
private:
    TreeNode* construct(vector<int>& preorder, int& pos, int minVal, int maxVal) {
        if (pos >= preorder.size()) {
            return nullptr;
        }

        int value = preorder[pos];
        if (value < minVal or value > maxVal) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(value);
        pos += 1;
        root -> left = construct(preorder, pos, minVal, value);
        root -> right = construct(preorder, pos, value, maxVal);
        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int pos = 0;
        return construct(preorder, pos, INT_MIN, INT_MAX);
    }
};

class Solution1 { // simple recursive
private:
    TreeNode* construct(int start, int end, vector<int> num) {
        if (start >= end) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(num[start]);
        int l = start + 1;
        int r = l;
        while (r < end and num[r] < num[start]) {
            r += 1;
        }
        root -> left = construct(l, r, num);
        root -> right = construct(r, end, num);
        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return construct(0, preorder.size(), preorder);
    }
};
