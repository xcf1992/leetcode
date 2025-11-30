/*
https://leetcode.com/problems/change-the-root-of-a-binary-tree/description/
1666. Change the Root of a Binary Tree

Given the root of a binary tree and a leaf node, reroot the tree so that the leaf is the new root.

You can reroot the tree with the following steps for each node cur on the path starting from the leaf up to the
root​​​ excluding the root:

If cur has a left child, then that child becomes cur's right child.
cur's original parent becomes cur's left child. Note that in this process the original parent's pointer to cur becomes
null, making it have at most one child. Return the new root of the rerooted tree.

Note: Ensure that your solution sets the Node.parent pointers correctly after rerooting or you will receive "Wrong
Answer".



Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], leaf = 7
Output: [7,2,null,5,4,3,6,null,null,null,1,null,null,0,8]
Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], leaf = 0
Output: [0,1,null,3,8,5,null,null,null,6,2,null,null,7,4]


Constraints:

The number of nodes in the tree is in the range [2, 100].
-109 <= Node.val <= 109
All Node.val are unique.
leaf exist in the tree.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};

class Solution {
public:
    Node* flipBinaryTree(Node* root, Node* leaf) {
        Node* prev = nullptr;
        Node* cur = leaf;
        Node* cur_parent = nullptr;
        while (prev != root) {
            if (cur != root) {
                if (cur->left != nullptr) {
                    cur->right = cur->left;
                    cur->left = nullptr;
                }

                cur_parent = cur->parent;
                cur->left = cur_parent;

                if (cur_parent->left == cur) {
                    cur_parent->left = nullptr;
                }
                if (cur_parent->right == cur) {
                    cur_parent->right = nullptr;
                }
            }

            cur->parent = prev;
            prev = cur;
            cur = cur_parent;
        }
        return leaf;
    }
};

class Solution {
private:
    void flip(Node* cur, Node* prev) {
        if (cur->parent == nullptr) {
            if (cur->left == prev) {
                cur->left = nullptr;
            }
            if (cur->right == prev) {
                cur->right = nullptr;
            }
            cur->parent = prev;
            return;
        }

        if (cur->right == prev) {
            cur->right = cur->left;
        }

        Node* cur_parent = cur->parent;
        cur->parent = prev;
        cur->left = cur_parent;
        flip(cur_parent, cur);
    }

public:
    Node* flipBinaryTree(Node* root, Node* leaf) {
        flip(leaf, nullptr);
        return leaf;
    }
};