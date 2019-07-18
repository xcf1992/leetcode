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