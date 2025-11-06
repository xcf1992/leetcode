/*
1302. Deepest Leaves Sum
https://leetcode.com/problems/deepest-leaves-sum/

Given a binary tree, return the sum of values of its deepest leaves.

Example 1:
                    1
            2              3
        4      5              6
       7                        8
Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
Output: 15

Constraints:
The number of nodes in the tree is between 1 and 10^4.
The value of nodes is between 1 and 100.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
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
private:
    void dfs(TreeNode* root, int& result, int depth, int& maxDepth) {
        if (root == nullptr) {
            return;
        }

        depth += 1;
        if (root->left == nullptr and root->right == nullptr) {
            if (depth >= maxDepth) {
                if (depth > maxDepth) {
                    result = 0;
                }
                result += root->val;
                maxDepth = depth;
            }
        }

        dfs(root->left, result, depth, maxDepth);
        dfs(root->right, result, depth, maxDepth);
    }

public:
    int deepestLeavesSum(TreeNode* root) {
        int result = 0;
        int maxDepth = 0;
        dfs(root, result, 0, maxDepth);
        return result;
    }
};