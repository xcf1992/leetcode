/*
16. 3Sum Closest
Given an array nums of n integers and an integer target,
find three integers in nums such that the sum is closest to target.
Return the sum of the three integers.
You may assume that each input would have exactly one solution.

Example:

Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        int n = num.size();
        if (n == 3) {
            return num[0] + num[1] + num[2];
        }
        sort(num.begin(), num.end());

        int result = num[0] + num[1] + num[2];
        for (int i = 0; i < n - 2; i++) {
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                int sum = num[i] + num[left] + num[right];
                if (abs(sum - target) < abs(result - target)) {
                    result = sum;
                }

                if (sum == target) {
                    return sum;
                }

                if (sum < target) {
                    left++;
                } else if (sum > target) {
                    right--;
                }
            }
        }
        return result;
    }
};