/*
1080. Insufficient Nodes in Root to Leaf Paths
https://leetcode.com/problems/insufficient-nodes-in-root-to-leaf-paths/

Given the root of a binary tree,
consider all root to leaf paths:
paths from the root to any leaf.
(A leaf is a node with no children.)

A node is insufficient if every such root to leaf path intersecting this node has sum strictly less than limit.
Delete all insufficient nodes simultaneously,
and return the root of the resulting binary tree.

Example 1:
                        1
                /               \
            2                       3
        /       \               /        \
       4        -99            -99         7
      /  \     /  \           /  \        /  \
      8  9    -99  -99       12  13      -99  14
Input: root = [1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14], limit = 1
                        1
                /               \
            2                     3
        /                           \
       4                              7
      /  \                              \
      8  9                              14
Output: [1,2,3,4,null,null,7,8,9,null,14]

Example 2:
                        5
                /               \
            4                     8
        /                      /    \
       11                     17      4
      /  \                          /   \
     7    1                        5     3
Input: root = [5,4,8,11,null,17,4,7,1,null,null,5,3], limit = 22
                        5
                /               \
            4                     8
        /                      /    \
       11                     17      4
      /                             /
     7                             5
Output: [5,4,8,11,null,17,4,7,null,null,null,5]

Note:
The given tree will have between 1 and 5000 nodes.
-10^5 <= node.val <= 10^5
-10^9 <= limit <= 10^9
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

class Solution {
private:
    bool isSufficient(TreeNode* root, int sum, int limit) {
        if (root == nullptr) {
            return false;
        }

        sum += root -> val;
        if (root -> left == nullptr and root -> right == nullptr) {
            return sum >= limit;
        }

        bool leftSufficient = isSufficient(root -> left, sum, limit);
        if (!leftSufficient) {
            root -> left = nullptr;
        }
        bool rightSufficient = isSufficient(root -> right, sum, limit);
        if (!rightSufficient) {
            root -> right = nullptr;
        }
        return leftSufficient or rightSufficient;
    }
public:
    TreeNode* sufficientSubset(TreeNode *root, int limit) {
        return isSufficient(root, 0, limit) ? root : nullptr;
    }
};
