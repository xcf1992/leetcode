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
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // If either p or q matches is the root, report
        // the presence by returning root (Note that if a key is
        // ancestor of other, then the ancestor key becomes LCA
        if (root == nullptr || root == p || root== q) {
            return root;
        }

        // Search in left and right subtrees
        TreeNode *left_lca  = lowestCommonAncestor(root->left, p, q);
        TreeNode *right_lca = lowestCommonAncestor(root->right, p, q);

        // If both of the above calls return Non-nullptr, then one key
        // is present in once subtree and other is present in other,
        // So this node is the LCA
        if (left_lca && right_lca) {
            return root;
        }

        // Otherwise check if left subtree or right subtree is LCA
        return (left_lca != nullptr)? left_lca: right_lca;
    }
};

int main() {
    Solution s;
    return 0;
}