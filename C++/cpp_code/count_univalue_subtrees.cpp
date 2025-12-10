/*
250. Count Univalue Subtrees
https://leetcode.com/problems/count-univalue-subtrees/

Given a binary tree, count the number of uni-value subtrees.
A Uni-value subtree means all nodes of the subtree have the same value.

Example :
Input:
root = [5,1,5,5,5,null,5]
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
#include <climits>
#include <map>

using namespace std;

class Solution {
private:
    int count(TreeNode* root, int& result) {
        int left = root->val;
        if (root->left != nullptr) {
            left = count(root->left, result);
        }

        int right = root->val;  // we have to do this in case one of the child is null while another is not
        if (root->right != nullptr) {
            right = count(root->right, result);
        }

        if (root->val == left and root->val == right) {
            result += 1;
            return root->val;
        }
        return INT_MAX;
    }

public:
    int countUnivalSubtrees(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int result = 0;
        count(root, result);
        return result;
    }
};