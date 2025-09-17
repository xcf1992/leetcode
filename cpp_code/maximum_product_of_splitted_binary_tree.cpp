/*
1343. Maximum Product of Splitted Binary Tree
https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/

Given a binary tree root.
Split the binary tree into two subtrees by removing 1 edge
such that the product of the sums of the subtrees are maximized.
Since the answer may be too large,
return it modulo 10^9 + 7.

Example 1:
        1                     |       1
    2       3  ===>    2      |         3
   4 5     6          4  5    |        6
Input: root = [1,2,3,4,5,6]
Output: 110
Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)

Example 2:
Input: root = [1,null,2,3,4,null,null,5,6]
Output: 90
Explanation:  Remove the red edge and get 2 binary trees with sum 15 and 6.Their product is 90 (15*6)

Example 3:
Input: root = [2,3,9,10,7,8,6,5,4,11,1]
Output: 1025

Example 4:
Input: root = [1,1]
Output: 1

Constraints:
Each tree has at most 50000 nodes and at least 2 nodes.
Each node's value is between [1, 10000].
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int MOD = 1e9 + 7;

    void getSum(long& sum, TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        sum += root -> val;
        getSum(sum, root -> left);
        getSum(sum, root -> right);
    }

    int getMaxProduct(long sum, long& minGap, TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int lSum = getMaxProduct(sum, minGap, root -> left);
        int rSum = getMaxProduct(sum, minGap, root -> right);
        int curSum = root -> val + lSum + rSum;
        int gap = abs((sum - curSum) - curSum);
        if (minGap > gap) {
            minGap = gap;
        }
        return curSum;
    }
public:
    int maxProduct(TreeNode* root) {
        long sum = 0;
        getSum(sum, root);

        long gap = sum;
        getMaxProduct(sum, gap, root);
        return ((sum + gap) * (sum - gap) / 4) % MOD;
    }
};
