/*
156. Binary Tree Upside Down
https://leetcode.com/problems/binary-tree-upside-down/

Given a binary tree where all the right nodes are either leaf nodes with a sibling
(a left node that shares the same parent node) or empty,
flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes.
Return the new root.

Example:
Input: [1,2,3,4,5]
    1
   / \
  2   3
 / \
4   5
Output: return the root of the binary tree [4,5,2,#,#,3,1]
   4
  / \
 5   2
    / \
   3   1
Clarification:
Confused what [4,5,2,#,#,3,1] means? Read more below on how binary tree is serialized on OJ.

The serialization of a binary tree follows a level order traversal,
where '#' signifies a path terminator where no node exists below.
Here's an example:
   1
  / \
 2   3
    /
   4
    \
     5
The above binary tree is serialized as [1,2,3,#,#,4,#,#,5].
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    TreeNode *upsideDownBinaryTree(TreeNode *root) {
        if (root == nullptr or root -> left == nullptr) {
            return root;
        }

        TreeNode *lc = root -> left;
        TreeNode *rc = root -> right;
        root -> right = nullptr;
        root -> left = nullptr;

        TreeNode* newRoot = upsideDownBinaryTree(lc);
        TreeNode* cur = newRoot;
        while (cur -> right != nullptr) {
            cur = cur -> right;
        }
        cur -> right = root;
        cur -> left = rc;
        return newRoot;
    }
};
