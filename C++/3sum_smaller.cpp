/*
 Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.
 
 For example, given nums = [-2, 0, 1, 3], and target = 2.
 
 Return 2. Because there are two triplets which sums are less than 2:
 
 [-2, 0, 1]
 [-2, 0, 3]
 Follow up:
 Could you solve it in O(n2) runtime?
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
using namespace std;

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        if (nums.empty()) {
            return 0;
        }
        sort(nums.begin(), nums.end());
        int result = 0;
        for (int left = 0; left < nums.size() - 2; left++) {
            if (nums[left] + nums[left + 1] + nums[left + 2] >= target) {
                break;
            }
            
            for (int right = nums.size() - 1; right > left + 1; right--) {
                int mid = left + 1;
                while (mid < right && nums[left] + nums[mid] + nums[right] < target) {
                    mid += 1;
                }
                result += mid - left - 1;
            }
        }
        return result;
    }
};
