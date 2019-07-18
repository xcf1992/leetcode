/*
 Given a complete binary tree, count the number of nodes.

 Definition of a complete binary tree from Wikipedia:
 In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
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
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftHeight = 1;
        TreeNode* leftC = root -> left;
        while (leftC != nullptr) {
            leftC = leftC -> left;
            leftHeight += 1;
        }

        int rightHeight = 1;
        TreeNode* rightC = root -> right;
        while (rightC != nullptr) {
            rightC = rightC -> right;
            rightHeight += 1;
        }

        return leftHeight == rightHeight ? pow(2, leftHeight) - 1 : 1 + countNodes(root -> left) + countNodes(root -> right);
    }
};
