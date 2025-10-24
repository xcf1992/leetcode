/*
543. Diameter of Binary Tree

Given a binary tree,
you need to compute the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
This path may or may not pass through the root.

Example:
Given a binary tree
          1
         / \
        2   3
       / \
      4   5
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note:
The length of path between two nodes is represented by the number of edges between them.
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
    int find(TreeNode* root, int& result) {
        if (root == nullptr) {
            return 0;
        }

        int leftLength = find(root -> left, result);
        int rightLength = find(root -> right, result);
        result = max(result, leftLength + rightLength + 1);
        return max(leftLength, rightLength) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int result = 0;
        find(root, result);
        return result - 1;
    }
};
