/*
https://leetcode.com/problems/merge-bsts-to-create-single-bst/
1932. Merge BSTs to Create Single BST

You are given n BST (binary search tree) root nodes for n separate BSTs stored in an array trees (0-indexed). Each BST
in trees has at most 3 nodes, and no two roots have the same value. In one operation, you can:

Select two distinct indices i and j such that the value stored at one of the leaves of trees[i] is equal to the root
value of trees[j]. Replace the leaf node in trees[i] with trees[j]. Remove trees[j] from trees. Return the root of the
resulting BST if it is possible to form a valid BST after performing n - 1 operations, or null if it is impossible to
create a valid BST.

A BST (binary search tree) is a binary tree where each node satisfies the following property:

Every node in the node's left subtree has a value strictly less than the node's value.
Every node in the node's right subtree has a value strictly greater than the node's value.
A leaf is a node that has no children.



Example 1:


Input: trees = [[2,1],[3,2,5],[5,4]]
Output: [3,2,5,1,null,4]
Explanation:
In the first operation, pick i=1 and j=0, and merge trees[0] into trees[1].
Delete trees[0], so trees = [[3,2,5,1],[5,4]].

In the second operation, pick i=0 and j=1, and merge trees[1] into trees[0].
Delete trees[1], so trees = [[3,2,5,1,null,4]].

The resulting tree, shown above, is a valid BST, so return its root.
Example 2:


Input: trees = [[5,3,8],[3,2,6]]
Output: []
Explanation:
Pick i=0 and j=1 and merge trees[1] into trees[0].
Delete trees[1], so trees = [[5,3,8,2,6]].

The resulting tree is shown above. This is the only valid operation that can be performed, but the resulting tree is not
a valid BST, so return null. Example 3:


Input: trees = [[5,4],[3]]
Output: []
Explanation: It is impossible to perform any operations.


Constraints:

n == trees.length
1 <= n <= 5 * 104
The number of nodes in each tree is in the range [1, 3].
Each node in the input may have children but no grandchildren.
No two roots of trees have the same value.
All the trees in the input are valid BSTs.
1 <= TreeNode.val <= 5 * 104.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include "extra_data_types.hpp"
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void find_leaves(TreeNode* node, unordered_set<int>& leaves) {
        if (node == nullptr) {
            return;
        }

        if (node->left == nullptr && node->right == nullptr) {
            leaves.insert(node->val);
            return;
        }

        find_leaves(node->left, leaves);
        find_leaves(node->right, leaves);
    }

    void merge(TreeNode* node, unordered_map<int, TreeNode*>& roots) {
        if (node == nullptr) {
            return;
        }

        if (node->left == nullptr && node->right == nullptr && roots.find(node->val) != roots.end()) {
            // it is a current leaf node and its value exist in the roots mao, then merge it
            TreeNode* sub = roots[node->val];
            node->left = sub->left;
            node->right = sub->right;
            roots.erase(node->val);
        }

        merge(node->left, roots);
        merge(node->right, roots);
    }

    bool is_valid_bst(TreeNode* node, long low, long high) {
        if (node == nullptr) {
            return true;
        }

        if (node->val <= low || node->val >= high) {
            return false;
        }

        return is_valid_bst(node->left, low, node->val) && is_valid_bst(node->right, node->val, high);
    }

    TreeNode* canMerge(vector<TreeNode*>& trees) {
        if (trees.size() == 1) {
            return trees[0];
        }

        unordered_set<int> leaves;
        unordered_map<int, TreeNode*> roots;  // for all main roots
        for (TreeNode* t : trees) {
            roots[t->val] = t;       // building root map
            find_leaves(t, leaves);  // collecting leaf nodes
        }

        TreeNode* root = nullptr;
        for (TreeNode* t : trees) {
            if (leaves.find(t->val) != leaves.end()) {
                continue;
            }
            if (root != nullptr) {
                return nullptr;
            }
            root = t;
        }

        if (!root) {
            return nullptr;
        }

        roots.erase(root->val);
        merge(root, roots);
        if (!roots.empty()) {
            return nullptr;
        }

        if (!is_valid_bst(root, LONG_MIN, LONG_MAX)) {
            return nullptr;
        };
        return root;
    }
};