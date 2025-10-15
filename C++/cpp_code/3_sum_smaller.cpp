/*
259. 3Sum Smaller
Given an array of n integers nums and a target,
find the number of index triplets i, j, k with 0 <= i < j < k < n
that satisfy the condition nums[i] + nums[j] + nums[k] < target.

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
        int n = nums.size();
        if (n < 3) {
            return 0;
        }

        sort(nums.begin(), nums.end());
        int result = 0;
        for (int left = 0; left < n - 2; left++) {
            if (nums[left] + nums[left + 1] + nums[left + 2] >= target) {
                break;
            }

            int mid = left + 1;
            int right = n - 1;
            int limit = target - nums[left];
            while (mid < right) {
                if (nums[mid] + nums[right] < limit) {
                    result += right - mid;
                    mid += 1;
                }
                else {
                    right -= 1;
                }
            }
        }
        return result;
    }
};
