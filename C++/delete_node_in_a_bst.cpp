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