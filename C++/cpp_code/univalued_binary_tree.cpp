/*
 965. Univalued Binary Tree
 A binary tree is univalued if every node in the tree has the same value.

 Return true if and only if the given tree is univalued.

 Example 1:


 Input: [1,1,1,1,1,null,1]
 Output: true
 Example 2:


 Input: [2,2,2,5,2]
 Output: false


 Note:

 The number of nodes in the given tree will be in the range [1, 100].
 Each node's value will be an integer in the range [0, 99].
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
public:
    bool isUnivalTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        if (root->left == nullptr and root->right == nullptr) {
            return true;
        }

        if (root->left != nullptr and root->val != root->left->val) {
            return false;
        }

        if (root->right != nullptr and root->val != root->right->val) {
            return false;
        }
        return isUnivalTree(root->left) and isUnivalTree(root->right);
    }
};