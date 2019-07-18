#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }

        TreeNode * left_child = root -> left;
        TreeNode * right_child = root -> right;
        root -> left = invertTree(right_child);
        root -> right = invertTree(left_child);

        return root;
    }
};
