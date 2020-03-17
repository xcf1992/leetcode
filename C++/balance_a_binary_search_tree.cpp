/*
1382. Balance a Binary Search Tree
https://leetcode.com/problems/balance-a-binary-search-tree/

Given a binary search tree,
return a balanced binary search tree with the same node values.

A binary search tree is balanced if and only if
the depth of the two subtrees of every node never differ by more than 1.

If there is more than one answer, return any of them.

Example 1:
1                                 2
    2           ===>        1           3
        3                                   4
            4
Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2,null,null] is also correct.

Constraints:
The number of nodes in the tree is between 1 and 10^4.
The tree nodes will have distinct values between 1 and 10^5.
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
    TreeNode* vectorToBalancedTree(int start, int end, vector<int>& nums) {
        if (start >= end) {
            return nullptr;
        }

        int mid = start + (end - start) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root -> left = vectorToBalancedTree(start, mid, nums);
        root -> right = vectorToBalancedTree(mid + 1, end, nums);
        return root;
    }

    void balancedTreeToVector(TreeNode* root, vector<int>& nums) {
        if (root == nullptr) {
            return;
        }

        balancedTreeToVector(root -> left, nums);
        nums.push_back(root -> val);
        balancedTreeToVector(root -> right, nums);
    }
public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> nums;
        balancedTreeToVector(root, nums);
        return vectorToBalancedTree(0, nums.size(), nums);
    }
};
