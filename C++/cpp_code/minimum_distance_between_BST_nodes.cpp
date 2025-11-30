//
//  minimum_distance_between_BST_nodes.cpp
//  C++
//
//  Created by Chenfu Xie on 2/11/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

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
#include <map>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int result;
    TreeNode* prev;

    void traverse(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        traverse(root->left);
        if (prev != nullptr) {
            result = min(result, root->val - prev->val);
        }
        prev = root;
        traverse(root->right);
    }

public:
    int minDiffInBST(TreeNode* root) {
        result = INT_MAX;
        prev = nullptr;
        traverse(root);
        return result;
    }
};