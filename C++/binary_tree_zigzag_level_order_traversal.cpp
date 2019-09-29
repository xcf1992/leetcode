/*
103. Binary Tree Zigzag Level Order Traversal
https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

Given a binary tree, return the zigzag level order traversal of its nodes' values.
(ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]
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
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        vector<vector<int>> result;
        queue<TreeNode*> bfs;
        bfs.push(root);
        while (!bfs.empty()) {
            int curSize = bfs.size();
            vector<int> row;
            for (int i = 0; i < curSize; ++i) {
                TreeNode* cur = bfs.front();
                bfs.pop();

                row.push_back(cur -> val);
                if (cur -> left) {
                    bfs.push(cur -> left);
                }
                if (cur -> right) {
                    bfs.push(cur -> right);
                }
            }
            result.push_back(row);
        }

        for (int i = 1; i < result.size(); i += 2) {
            reverse(result[i].begin(), result[i].end());
        }
        return result;
    }
};
