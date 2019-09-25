/*
776. Split BST
https://leetcode.com/problems/split-bst/

Given a Binary Search Tree (BST) with root node root,
and a target value V,
split the tree into two subtrees where one subtree has nodes that are all smaller or equal to the target value,
while the other subtree has all nodes that are greater than the target value.
It's not necessarily the case that the tree contains a node with value V.

Additionally, most of the structure of the original tree should remain.
Formally, for any child C with parent P in the original tree,
if they are both in the same subtree after the split,
then node C should still have the parent P.

You should output the root TreeNode of both subtrees after splitting, in any order.

Example 1:
Input: root = [4,2,6,1,3,5,7], V = 2
Output: [[2,1],[4,3,6,null,null,5,7]]
Explanation:
Note that root, output[0], and output[1] are TreeNode objects, not arrays.
The given tree [4,2,6,1,3,5,7] is represented by the following diagram:
     4
   /   \
  2      6
 / \    / \
1   3  5   7
while the diagrams for the outputs are:
      4
    /   \
   3     6      and     2
  / \                  /
 5   7                1

Note:
The size of the BST will not exceed 50.
The BST is always valid and each node's value is different.
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

class Solution {
private:
    void insert(TreeNode* root, TreeNode* node) {
        if (root == nullptr or node == nullptr) {
            return;
        }

        if (root -> val > node -> val) {
            if (root -> left == nullptr) {
                root -> left = node;
            }
            else {
                insert(root -> left, node);
            }
            return;
        }

        if (root -> right == nullptr) {
            root -> right = node;
        }
        else {
            insert(root -> right, node);
        }
    }
public:
    vector<TreeNode*> splitBST(TreeNode* root, int V) {
        if (root == nullptr) {
            return {nullptr, nullptr};
        }

        if (root -> val <= V) {
            TreeNode* rightChild = root -> right;
            root -> right = nullptr;
            vector<TreeNode*> rightSplit = splitBST(rightChild, V);
            insert(root, rightSplit[0]);
            return {root, rightSplit[1]};
        }

        TreeNode* leftChild = root -> left;
        root -> left = nullptr;
        vector<TreeNode*> leftSplit = splitBST(leftChild, V);
        insert(root, leftSplit[1]);
        return {leftSplit[0], root};
    }
};

class Solution1 {
private:
    void insert(TreeNode* root, TreeNode* cur) {
        TreeNode* newPos = root;
        while (true) {
            if (cur -> val > newPos -> val) {
                if (newPos -> right != nullptr) {
                    newPos = newPos -> right;
                }
                else {
                    newPos -> right = cur;
                    break;
                }
            }
            else {
                if (newPos -> left != nullptr) {
                    newPos = newPos -> left;
                }
                else {
                    newPos -> left = cur;
                    break;
                }
            }
        }
    }
    void split(vector<TreeNode*>& result, TreeNode* cur, int V) {
        if (cur == nullptr) {
            return;
        }

        if (cur -> val > V) {
            if (result[0] == nullptr) {
                result[0] = cur;
            }
            else {
                insert(result[0], cur);
            }
            TreeNode* next = cur -> left;
            cur -> left = nullptr;
            split(result, next, V);
        }
        else {
            if (result[1] == nullptr) {
                result[1] = cur;
            }
            else {
                insert(result[1], cur);
            }
            TreeNode* next = cur -> right;
            cur -> right = nullptr;
            split(result, next, V);
        }
    }
public:
    vector<TreeNode*> splitBST(TreeNode* root, int V) {
        vector<TreeNode*> result(2, nullptr);
        split(result, root, V);
        return result;
    }
};
