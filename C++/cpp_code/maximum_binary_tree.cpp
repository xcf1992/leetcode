/*
654. Maximum Binary Tree
https://leetcode.com/problems/maximum-binary-tree/

Given an integer array with no duplicates.
A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:
       6
    /     \
   3       5
    \     /
     2   0
      \
       1

Note:
The size of the given array will be in the range [1,1000].
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
    TreeNode *construct(int start, int end, vector<int> &nums) {
        if (start >= end) {
            return nullptr;
        }

        int maxIndex = start;
        for (int i = start + 1; i < end; ++i) {
            if (nums[i] > nums[maxIndex]) {
                maxIndex = i;
            }
        }

        TreeNode *root = new TreeNode(nums[maxIndex]);
        root->left = construct(start, maxIndex, nums);
        root->right = construct(maxIndex + 1, end, nums);
        return root;
    }

public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        return construct(0, nums.size(), nums);
    }
};

// We scan numbers from left to right, build the tree one node by one step;
class Solution1 {
private:
    TreeNode *insert(TreeNode *root, int num) {
        if (root == nullptr) {
            TreeNode *newRoot = new TreeNode(num);
            return newRoot;
        }
        if (num > root->val) {
            TreeNode *newRoot = new TreeNode(num);
            newRoot->left = root;
            return newRoot;
        }
        root->right = insert(root->right, num);
        return root;
    }

public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        TreeNode *root = nullptr;
        for (int num: nums) {
            root = insert(root, num);
        }
        return root;
    }
};