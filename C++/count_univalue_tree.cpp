//
//  count_univalue_tree.cpp
//  C++
//
//  Created by Chenfu Xie on 2/28/18.
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

/*
 Given a binary tree, count the number of uni-value subtrees.
 
 A Uni-value subtree means all nodes of the subtree have the same value.
 
 For example:
 Given binary tree,
 5
 / \
 1   5
 / \   \
 5   5   5
 return 4.
 
*/


struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
private:
    int count(TreeNode* root, int& result) {
        int left = root -> val;
        int right = root -> val;
        if (root -> left != nullptr) {
            left = count(root -> left, result);
        }
        if (root -> right != nullptr) {
            right = count(root -> right, result);
        }
        
        if (root -> val == left && root -> val == right) {
            result += 1;
            return root -> val;
        }
        return INT_MAX;
    }
public:
    int countUnivalSubtrees(TreeNode* root) {
        int result = 0;
        if (root == nullptr) {
            return result;
        }
        count(root, result);
        return result;
    }
};
