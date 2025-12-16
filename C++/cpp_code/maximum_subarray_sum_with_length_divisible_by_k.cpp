/*
https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/description/
3381. Maximum Subarray Sum With Length Divisible by K

You are given an array of integers nums and an integer k.

Return the maximum sum of a subarray of nums, such that the size of the subarray is divisible by k.



Example 1:

Input: nums = [1,2], k = 1

Output: 3

Explanation:

The subarray [1, 2] with sum 3 has length equal to 2 which is divisible by 1.

Example 2:

Input: nums = [-1,-2,-3,-4,-5], k = 4

Output: -10

Explanation:

The maximum sum subarray is [-1, -2, -3, -4] which has length equal to 4 which is divisible by 4.

Example 3:

Input: nums = [-5,1,2,-3,4], k = 2

Output: 4

Explanation:

The maximum sum subarray is [1, 2, -3, 4] which has length equal to 4 which is divisible by 2.



Constraints:

1 <= k <= nums.length <= 2 * 105
-109 <= nums[i] <= 109
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
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> min_prefix_sum(k, LONG_LONG_MAX);
        min_prefix_sum[0] = 0;
        long long cur_sum = 0;
        long long rst = LONG_LONG_MIN;
        for (int i = 0; i < n; i++) {
            cur_sum += nums[i];
            if (min_prefix_sum[(i + 1) % k] != LONG_LONG_MAX) {
                rst = max(rst, cur_sum - min_prefix_sum[(i + 1) % k]);
            }
            min_prefix_sum[(i + 1) % k] = min(min_prefix_sum[(i + 1) % k], cur_sum);
        }
        return rst;
    }
};
