/*
 Consider all the leaves of a binary tree.  From left to right order, the values of those leaves form a leaf value
 sequence.

          3
       /      \
      5        1
    /  \     /  \
   6   2    9    8
      / \
     7   4

 For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9, 8).

 Two binary trees are considered leaf-similar if their leaf value sequence is the same.

 Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.



 Note:

 Both of the given trees will have between 1 and 100 nodes.

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
private:
    void getLeaves(TreeNode* root, vector<int>& leaves) {
        if (root == nullptr) {
            return;
        }
        if (root->left == nullptr and root->right == nullptr) {
            leaves.push_back(root->val);
            return;
        }
        getLeaves(root->left, leaves);
        getLeaves(root->right, leaves);
    }

public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> leaves1;
        getLeaves(root1, leaves1);
        vector<int> leaves2;
        getLeaves(root2, leaves2);
        if (leaves1.size() != leaves2.size()) {
            return false;
        }
        for (int i = 0; i < leaves1.size(); i++) {
            if (leaves1[i] != leaves2[i]) {
                return false;
            }
        }
        return true;
    }
};