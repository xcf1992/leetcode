/*
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iv/description/
1676. Lowest Common Ancestor of a Binary Tree IV

Given the root of a binary tree and an array of TreeNode objects nodes, return the lowest common ancestor (LCA) of all
the nodes in nodes. All the nodes will exist in the tree, and all values of the tree's nodes are unique.

Extending the definition of LCA on Wikipedia: "The lowest common ancestor of n nodes p1, p2, ..., pn in a binary tree T
is the lowest node that has every pi as a descendant (where we allow a node to be a descendant of itself) for every
valid i". A descendant of a node x is a node y that is on the path from node x to some leaf node.



Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [4,7]
Output: 2
Explanation: The lowest common ancestor of nodes 4 and 7 is node 2.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [1]
Output: 1
Explanation: The lowest common ancestor of a single node is the node itself.

Example 3:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [7,6,2,4]
Output: 5
Explanation: The lowest common ancestor of the nodes 7, 6, 2, and 4 is node 5.


Constraints:

The number of nodes in the tree is in the range [1, 104].
-109 <= Node.val <= 109
All Node.val are unique.
All nodes[i] will exist in the tree.
All nodes[i] are distinct.
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

class Solution {
private:
    TreeNode* find(TreeNode* root, unordered_set<int>& visited) {
        if (root == nullptr || visited.find(root->val) != visited.end()) {
            return root;
        }

        TreeNode* l_rst = find(root->left, visited);
        TreeNode* r_rst = find(root->right, visited);
        if (l_rst && r_rst) {
            return root;
        }

        if (l_rst) {
            return l_rst;
        }

        if (r_rst) {
            return r_rst;
        }

        return nullptr;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*>& nodes) {
        unordered_set<int> visited;
        for (const TreeNode* node : nodes) {
            visited.insert(node->val);
        }
        return find(root, visited);
    }
};
