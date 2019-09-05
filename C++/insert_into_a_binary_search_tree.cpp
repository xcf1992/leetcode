/*
 Given the root node of a binary search tree (BST) and a value to be inserted into the tree, insert the value into the BST. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.

 Note that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

 For example,

 Given the tree:
     4
    / \
   2   7
  / \
 1   3
 And the value to insert: 5
 You can return this binary search tree:

        4
     /    \
    2      7
   / \    /
  1   3  5
 This tree is also valid:

      5
    /   \
   2     7
  / \
 1   3
      \
       4
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }

        if (val > root -> val) {
            root -> right = insertIntoBST(root -> right, val);
        }
        else {
            root -> left = insertIntoBST(root -> left, val);
        }
        return root;
    }
};
