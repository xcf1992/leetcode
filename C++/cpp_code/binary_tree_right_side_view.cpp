/*
199. Binary Tree Right Side View
https://leetcode.com/problems/binary-tree-right-side-view/

Given a binary tree, imagine yourself standing on the right side of it,
return the values of the nodes you can see ordered from top to bottom.

Example:
Input: [1,2,3,null,5,null,4]
Output: [1, 3, 4]
Explanation:
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        vector<int> result;
        queue<TreeNode*> bfs;
        bfs.push(root);
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                TreeNode* cur = bfs.front();
                bfs.pop();

                if (i == curSize - 1) {
                    result.push_back(cur->val);
                }
                if (cur->left != nullptr) {
                    bfs.push(cur->left);
                }
                if (cur->right != nullptr) {
                    bfs.push(cur->right);
                }
            }
        }
        return result;
    }
};