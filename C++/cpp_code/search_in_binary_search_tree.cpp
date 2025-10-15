/*
 Given the root node of a binary search tree (BST) and a value. You need to find the node in the BST that the node's value equals the given value. Return the subtree rooted with that node. If such node doesn't exist, you should return NULL.

 For example,

 Given the tree:
      4
     / \
    2   7
   / \
  1   3

 And the value to search: 2
 You should return this subtree:

   2
  / \
 1   3
 In the example above, if we want to search the value 5, since there is no node with value 5, we should return NULL.
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
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return root;
        }

        if (val == root -> val) {
            return root;
        }

        if (val > root -> val) {
            return searchBST(root -> right, val);
        }
        return searchBST(root -> left, val);
    }
};
