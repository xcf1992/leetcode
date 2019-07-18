/*
1123. Lowest Common Ancestor of Deepest Leaves
Given a rooted binary tree, return the lowest common ancestor of its deepest leaves.

Recall that:

The node of a binary tree is a leaf if and only if it has no children
The depth of the root of the tree is 0, and if the depth of a node is d, the depth of each of its children is d+1.
The lowest common ancestor of a set S of nodes is the node A with the largest depth such that every node in S is in the subtree with root A.


Example 1:

Input: root = [1,2,3]
Output: [1,2,3]
Explanation:
The deepest leaves are the nodes with values 2 and 3.
The lowest common ancestor of these leaves is the node with value 1.
The answer returned is a TreeNode object (not an array) with serialization "[1,2,3]".
Example 2:

Input: root = [1,2,3,4]
Output: [4]
Example 3:

Input: root = [1,2,3,4,5]
Output: [2,4,5]


Constraints:

The given tree will have between 1 and 1000 nodes.
Each node of the tree will have a distinct value between 1 and 1000.
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

class Solution { //99.25%
private:
    pair<TreeNode*, int> traverse(TreeNode* root) {
        if (!root) {
            return {nullptr, 0};
        }

        pair<TreeNode*, int> left = traverse(root->left);
        pair<TreeNode*, int> right = traverse(root->right);
        if (left.second > right.second) {
            return {left.first, left.second + 1};
        }
        if (left.second < right.second) {
            return {right.first, right.second + 1};
        }
        return {root, left.second + 1};
    }
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        return traverse(root).first;
    }
};

class Solution1 { // 92.98% created by Chenfu
private:
    void traverse(TreeNode* root, vector<TreeNode*>& parent, unordered_set<TreeNode*>& leaves, int cur, int& height) {
        if (root == nullptr) {
            return;
        }

        if (cur > height) {
            height = cur;
            leaves.clear();
        }
        if (cur == height) {
            leaves.insert(root);
        }

        if (root -> left != nullptr) {
            parent[root -> left -> val] = root;
        }
        if (root -> right != nullptr) {
            parent[root -> right -> val] = root;
        }

        traverse(root -> left, parent, leaves, cur + 1, height);
        traverse(root -> right, parent, leaves, cur + 1, height);
    }
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        vector<TreeNode*> parent(1001, nullptr);
        unordered_set<TreeNode*> leaves;
        int height = 0;
        traverse(root, parent, leaves, 0, height);

        while (leaves.size() > 1) {
            unordered_set<TreeNode*> newLeaves;
            for (auto it = leaves.begin(); it != leaves.end(); it++) {
                newLeaves.insert(parent[(*it) -> val]);
            }
            leaves = newLeaves;
        }
        return *leaves.begin();
    }
};
