//
//  binary_tree_longest_consecutive_sequence.cpp
//  C++
//
//  Created by Chenfu Xie on 3/1/18.
//  Copyright © 2018 Chenfu Xie. All rights reserved.
//

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
using namespace std;

/*
 Given a binary tree, find the length of the longest consecutive sequence path.
 
 The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).
 
 For example,
 1
  \
   3
  / \
 2   4
      \
       5
 Longest consecutive sequence path is 3-4-5, so return 3.
   2
    \
     3
    /
   2
  /
 1
 Longest consecutive sequence path is 2-3,not3-2-1, so return 2.
 */

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

class Solution {
private:
    void traverse(TreeNode* root, TreeNode* pre, int& result, int length) {
        if (pre != nullptr && root -> val != 1 + pre -> val) {
            result = max(result, length);
            length = 0;
        }
        
        length += 1;
        
        if (root -> left == nullptr && root -> right == nullptr) {
            result = max(result, length);
            return;
        }
        
        if (root -> left != nullptr) {
            traverse(root -> left, root, result, length);
        }
        
        if (root -> right != nullptr) {
            traverse(root -> right, root, result, length);
        }
    }
public:
    int longestConsecutive(TreeNode* root) {
        int result = 0;
        if (root == nullptr) {
            return result;
        }
        traverse(root, nullptr, result, 0);
        return result;
    }
};
