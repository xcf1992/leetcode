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
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    void getNums(TreeNode* root, vector<int>& nums) {
        if (root == nullptr) {
            return;
        }

        getNums(root -> left, nums);
        nums.push_back(root -> val);
        getNums(root -> right, nums);
        return;
    }
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> nums;
        getNums(root, nums);

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            if (nums[left] + nums[right] == k) {
                return true;
            }
            else if (nums[left] + nums[right] < k) {
                left += 1;
            }
            else {
                right -= 1;
            }
        }
        return false;
    }
};