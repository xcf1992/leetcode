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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    TreeNode* insert(TreeNode* root, int num) {
        if (root == nullptr) {
            TreeNode* newRoot = new TreeNode(num);
            return newRoot;
        }
        if (num > root -> val) {
            TreeNode* newRoot = new TreeNode(num);
            newRoot -> left = root;
            return newRoot;
        }
        root -> right = insert(root -> right, num);
        return root;
    }

public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        TreeNode* root = nullptr;
        for (int num : nums) {
            root = insert(root, num);
        }
        return root;
    }
};