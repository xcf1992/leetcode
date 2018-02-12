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
#include <stdio.h>
#include <map>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    int result;
    TreeNode* prev;
    void traverse(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        
        traverse(root -> left);
        if (prev != nullptr) {
            result = min(result, root -> val - prev -> val);
        }
        prev = root;
        traverse(root -> right);
    }
public:
    int minDiffInBST(TreeNode* root) {
        result = INT_MAX;
        prev = nullptr;
        traverse(root);
        return result;
    }
};
