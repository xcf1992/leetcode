/*
653. Two Sum IV - Input is a BST

Given a Binary Search Tree and a target number,
return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:
Input:
    5
   / \
  3   6
 / \   \
2   4   7
Target = 9
Output: True

Example 2:
Input:
    5
   / \
  3   6
 / \   \
2   4   7
Target = 28
Output: False
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
    void toList(TreeNode* root, vector<int>& nums) {
        if (root == nullptr) {
            return;
        }
        toList(root -> left, nums);
        nums.push_back(root -> val);
        toList(root -> right, nums);
    }
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> nums;
        toList(root, nums);

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            if (nums[left] + nums[right] == k) {
                return true;
            }

            if (nums[left] + nums[right] < k) {
                left += 1;
            }
            else {
                right -= 1;
            }
        }
        return false;
    }
};
