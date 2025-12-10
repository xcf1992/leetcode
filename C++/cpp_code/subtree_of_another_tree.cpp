/*
572. Subtree of Another Tree
https://leetcode.com/problems/subtree-of-another-tree/

Given two non-empty binary trees s and t,
check whether tree t has exactly the same structure and node values with a subtree of s.
A subtree of s is a tree consists of a node in s and all of this node's descendants.
The tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:
     3
    / \
   4   5
  / \
 1   2
Given tree t:
    4
  /  \
 1    2
Return true, because t has the same structure and node values with a subtree of s.

Example 2:
Given tree s:
     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.
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
#include <climits>

using namespace std;

class Solution {
private:
    bool sameTree(TreeNode* s, TreeNode* t) {
        if (s == nullptr and t == nullptr) {
            return true;
        }
        if (s == nullptr or t == nullptr) {
            return false;
        }

        if (s->val != t->val) {
            return false;
        }
        return sameTree(s->left, t->left) and sameTree(s->right, t->right);
    }

public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (t == nullptr) {
            return true;
        }
        if (s == nullptr) {
            return false;
        }
        return sameTree(s, t) or isSubtree(s->left, t) or isSubtree(s->right, t);
    }
};