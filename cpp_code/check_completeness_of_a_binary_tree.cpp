/*
958. Check Completeness of a Binary Tree
https://leetcode.com/problems/check-completeness-of-a-binary-tree/

Given a binary tree, determine if it is a complete binary tree.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last,
is completely filled, and all nodes in the last level are as far left as possible.
It can have between 1 and 2h nodes inclusive at the last level h.

Example 1:
                1
        2               3
      4   5           6
Input: [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.

Example 2:
                1
        2               3
      4   5               7
Input: [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.

Note:
The tree will have between 1 and 100 nodes.
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
/*
Use BFS to do a level order traversal,
add childrens to the bfs queue,
until we met the first empty node.

For a complete binary tree,
there should not be any node after we met an empty one.
*/
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        vector<TreeNode*> bfs;
        bfs.push_back(root);
        int count = 0;
        while (count < bfs.size() and bfs[count] != nullptr) {
            bfs.push_back(bfs[count] -> left);
            bfs.push_back(bfs[count] -> right);
            count += 1;
        }
        while (count < bfs.size() and bfs[count] == nullptr) {
            count += 1;
        }
        return count == bfs.size();
    }
};

class Solution1 {
public:
    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        queue<TreeNode*> bfs;
        bfs.push(root);
        int level = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            bool lastLevel = false;
            if (curSize != pow(2, level)) {
                lastLevel = true;
            }

            if (lastLevel) {
                while (!bfs.empty()) {
                    TreeNode* node = bfs.front();
                    bfs.pop();
                    if (node -> left != nullptr or node -> right != nullptr) {
                        return false;
                    }
                }
                return true;
            }

            bool completed = false; // means we should have already checked all the nodes in next level
            for (int i = 0; i < curSize; i++) {
                TreeNode* node = bfs.front();
                bfs.pop();
                if (!completed) {
                    if (node -> left == nullptr) {
                        completed = true;
                    }
                    else {
                        bfs.push(node -> left);
                    }

                    if (node -> right != nullptr) {
                        if (completed) {
                            return false;
                        }
                        else {
                            bfs.push(node -> right);
                        }
                    }
                    else {
                        completed = true;
                    }
                }
                else {
                    if (node -> left != nullptr or node -> right != nullptr) {
                        return false;
                    }
                }
            }
            level += 1;
        }
        return true;
    }
};
