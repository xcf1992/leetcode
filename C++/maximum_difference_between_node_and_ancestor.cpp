/*
1026. Maximum Difference Between Node and Ancestor
https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/

Given the root of a binary tree,
find the maximum value V for which there exists different nodes A and B where V = |A.val - B.val| and A is an ancestor of B.
(A node A is an ancestor of B if either: any child of A is equal to B, or any child of A is an ancestor of B.)

Example 1:
                            8
            /                           \
            3                            10
    /            \                          \
   1              6                          14
                 / \                        /
                4   7                      13

Input: [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation:
We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.

Note:
The number of nodes in the tree is between 2 and 5000.
Each node will have value between 0 and 100000.
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
    void getMaxDiff(TreeNode* node, int curMin, int curMax, int& result) {
        if (node == nullptr) {
            return;
        }

        int curVal = node -> val;
        result = max(result, max(abs(curVal - curMax), abs(curVal - curMin)));
        curMax = max(curMax, curVal);
        curMin = min(curMin, curVal);
        getMaxDiff(node -> left, curMin, curMax, result);
        getMaxDiff(node -> right, curMin, curMax, result);
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        int result = INT_MIN;
        getMaxDiff(root, root -> val, root -> val, result);
        return result;
    }
};
