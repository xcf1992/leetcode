/*
101. Symmetric Tree
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3


But the following [1,2,2,null,3,null,3] is not:

    1
   / \
  2   2
   \   \
   3    3


Note:
Bonus points if you could solve it both recursively and iteratively.
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
#include <set>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    bool symmetric(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr or root2 == nullptr) {
            return root1 == nullptr and root2 == nullptr;
        }
        if (root1 -> val != root2 -> val) {
            return false;
        }
        return symmetric(root1 -> left, root2 -> right) and symmetric(root1 -> right, root2 -> left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        if (root -> left == nullptr and root -> right == nullptr) {
            return true;
        }
        return symmetric(root -> left, root -> right);
    }
};
