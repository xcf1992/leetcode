/*
236. Lowest Common Ancestor of a Binary Tree
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia:
“The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants
(where we allow a node to be a descendant of itself).”

Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]

Example 1:
                                            3
                            5                               1
                    6               2                   0       8
                                7       4
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.


Note:

All of the nodes' values will be unique.
p and q are different and both values will exist in the binary tree.
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// If either p or q matches is the root, report
// the presence by returning root (Note that if a key is
// ancestor of other, then the ancestor key becomes LCA
// If both of the above calls return Non-nullptr, then one key
// is present in once subtree and other is present in other,
// So this node is the LCA
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr or root == p or root== q) {
            return root;
        }

        TreeNode *left_lca  = lowestCommonAncestor(root -> left, p, q);
        TreeNode *right_lca = lowestCommonAncestor(root -> right, p, q);
        if (left_lca and right_lca) {
            return root;
        }
        return left_lca != nullptr? left_lca: right_lca;
    }
};
