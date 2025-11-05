/*
1161. Maximum Level Sum of a Binary Tree
Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the smallest level X such that the sum of all the values of nodes at level X is maximal.


Example 1:
                            1
                7                   0
            7       -8
Input: [1,7,0,7,-8,null,null]
Output: 2
Explanation:
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.


Note:

The number of nodes in the given tree is between 1 and 10^4.
-10^5 <= node.val <= 10^5
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
public:
    int maxLevelSum(TreeNode *root) {
        queue<TreeNode *> bfs;
        bfs.push(root);
        int sum = INT_MIN;
        int level = 1;
        int result = -1;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            int curSum = 0;
            for (int i = 0; i < curSize; ++i) {
                TreeNode *curNode = bfs.front();
                bfs.pop();

                curSum += curNode->val;
                if (curNode->left != nullptr) {
                    bfs.push(curNode->left);
                }
                if (curNode->right != nullptr) {
                    bfs.push(curNode->right);
                }
            }
            if (curSum > sum) {
                sum = curSum;
                result = level;
            }
            level += 1;
        }
        return result;
    }
};