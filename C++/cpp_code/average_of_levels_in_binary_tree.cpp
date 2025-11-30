/*
637. Average of Levels in Binary Tree

Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].

Note:
The range of node's value is in the range of 32-bit signed integer.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> result;
        queue<TreeNode*> bfs;
        bfs.push(root);
        while (!bfs.empty()) {
            double sum = 0.0;
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                TreeNode* current = bfs.front();
                bfs.pop();

                sum += current->val;
                if (current->left != nullptr) {
                    bfs.push(current->left);
                }
                if (current->right != nullptr) {
                    bfs.push(current->right);
                }
            }
            result.push_back(sum / (double)curSize);
        }
        return result;
    }
};