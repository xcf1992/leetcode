/*
450. Delete Node in a BST
Given a root node reference of a BST and a key, delete the node with the given key in the BST. 
Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Note: Time complexity should be O(height of tree).

Example:

root = [5,3,6,2,4,null,7]
key = 3

    5
   / \
  3   6
 / \   \
2   4   7

Given key to delete is 3. So we find the node with value 3 and delete it.

One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

    5
   / \
  4   6
 /     \
2       7

Another valid answer is [5,2,6,null,4,null,7].

    5
   / \
  2   6
   \   \
    4   7
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
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
private:
    TreeNode* findTarget(TreeNode* root, TreeNode*& prev, int key) {
        if (root == nullptr || root -> val == key) {
            return root;
        }

        prev = root;
        if (key > root -> val) {
            return findTarget(root -> right, prev, key);
        }
        return findTarget(root -> left, prev, key);
    }

    void insertNode(TreeNode* root, TreeNode* node) {
        if (root == nullptr || node == nullptr) {
            return;
        }

        if (node -> val < root -> val) {
            if (root -> left == nullptr) {
                root -> left = node;
                return;
            }
            insertNode(root -> left, node);
        }
        else {
            if (root -> right == nullptr) {
                root -> right = node;
                return;
            }
            insertNode(root -> right, node);
        }
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode* fake = new TreeNode(INT_MAX);
        fake -> left = root;
        TreeNode* prev = fake;
        TreeNode* target = findTarget(root, prev, key);
        if (target == nullptr) {
            return root;
        }
        if (prev -> left == target) {
            prev -> left = nullptr;
        }
        else if (prev -> right == target) {
            prev -> right = nullptr;
        }
        insertNode(prev, target -> left);
        insertNode(prev, target -> right);
        target = nullptr;
        delete target;
        return fake -> left;
    }
};