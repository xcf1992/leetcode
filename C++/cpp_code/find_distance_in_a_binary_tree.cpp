/*
https://leetcode.com/problems/find-distance-in-a-binary-tree
1740. Find Distance in a Binary Tree

Given the root of a binary tree and two integers p and q, return the distance between the nodes of value p and value q
in the tree.

The distance between two nodes is the number of edges on the path from one to the other.



Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 0
Output: 3
Explanation: There are 3 edges between 5 and 0: 5-3-1-0.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 7
Output: 2
Explanation: There are 2 edges between 5 and 7: 5-2-7.
Example 3:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 5
Output: 0
Explanation: The distance between a node and itself is 0.


Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 109
All Node.val are unique.
p and q are values in the tree.
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
    TreeNode* lowest_common_ancestor(TreeNode* root, int startValue, int destValue) {
        if (root == nullptr || root->val == startValue || root->val == destValue) {
            return root;
        }

        TreeNode* lca_left = lowest_common_ancestor(root->left, startValue, destValue);
        TreeNode* lca_right = lowest_common_ancestor(root->right, startValue, destValue);
        if (lca_left != nullptr && lca_right != nullptr) {
            return root;
        }
        return lca_left != nullptr ? lca_left : lca_right;
    }

    bool get_distance(TreeNode* root, int val, int& distance) {
        if (root == nullptr) {
            return false;
        }

        if (root->val == val) {
            return true;
        }

        distance += 1;
        if (get_distance(root->left, val, distance)) {
            return true;
        }
        if (get_distance(root->right, val, distance)) {
            return true;
        }

        distance -= 1;
        return false;
    }

public:
    int findDistance(TreeNode* root, int p, int q) {
        TreeNode* lca = lowest_common_ancestor(root, p, q);

        int l_distance = 0;
        get_distance(lca, p, l_distance);
        int r_distance = 0;
        get_distance(lca, q, r_distance);
        return l_distance + r_distance;
    }
};