/*
 250. Count Univalue Subtrees
Given a binary tree, count the number of uni-value subtrees.

A Uni-value subtree means all nodes of the subtree have the same value.

Example :

Input:  root = [5,1,5,5,5,null,5]

              5
             / \
            1   5
           / \   \
          5   5   5

Output: 4
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int count(TreeNode* root, int& result) {
        int left = root -> val;
        int right = root -> val; // we have to do this in case one of the child is null while another is not
        if (root -> left != nullptr) {
            left = count(root -> left, result);
        }
        if (root -> right != nullptr) {
            right = count(root -> right, result);
        }

        if (root -> val == left and root -> val == right) {
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
