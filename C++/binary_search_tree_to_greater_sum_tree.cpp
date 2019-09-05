/*
 1038. Binary Search Tree to Greater Sum Tree

 Given the root of a binary search tree with distinct values, modify it so that every node has a new value equal to the sum of the values of the original tree that are greater than or equal to node.val.

 As a reminder, a binary search tree is a tree that satisfies these constraints:

 The left subtree of a node contains only nodes with keys less than the node's key.
 The right subtree of a node contains only nodes with keys greater than the node's key.
 Both the left and right subtrees must also be binary search trees.


 Example 1:



 Input: [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
 Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]


 Note:

 The number of nodes in the tree is between 1 and 100.
 Each node will have value between 0 and 100.
 The given tree is a binary search tree.
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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    void postOrderTraverse(TreeNode* root, TreeNode*& pre) {
        if (root == nullptr) {
            return;
        }

        postOrderTraverse(root -> right, pre);
        if (pre != nullptr) {
            (root -> val) += (pre -> val);
        }
        pre = root;
        postOrderTraverse(root -> left, pre);
        return;
    }
public:
    TreeNode* bstToGst(TreeNode* root) {
        TreeNode* pre = nullptr;
        postOrderTraverse(root, pre);
        return root;
    }
};
