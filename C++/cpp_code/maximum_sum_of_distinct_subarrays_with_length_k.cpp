/*
https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/description/
2461. Maximum Sum of Distinct Subarrays With Length K

You are given an integer array nums and an integer k. Find the maximum subarray sum of all the subarrays of nums that
meet the following conditions:

The length of the subarray is k, and
All the elements of the subarray are distinct.
Return the maximum subarray sum of all the subarrays that meet the conditions. If no subarray meets the conditions,
return 0.

A subarray is a contiguous non-empty sequence of elements within an array.



Example 1:

Input: nums = [1,5,4,2,9,9,9], k = 3
Output: 15
Explanation: The subarrays of nums with length 3 are:
- [1,5,4] which meets the requirements and has a sum of 10.
- [5,4,2] which meets the requirements and has a sum of 11.
- [4,2,9] which meets the requirements and has a sum of 15.
- [2,9,9] which does not meet the requirements because the element 9 is repeated.
- [9,9,9] which does not meet the requirements because the element 9 is repeated.
We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions
Example 2:

Input: nums = [4,4,4], k = 3
Output: 0
Explanation: The subarrays of nums with length 3 are:
- [4,4,4] which does not meet the requirements because the element 4 is repeated.
We return 0 because no subarrays meet the conditions.


Constraints:

1 <= k <= nums.length <= 105
1 <= nums[i] <= 105
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long rst = 0;
        long long cur_sum = 0;
        unordered_map<int, int> freq;
        for (int i = 0; i < k; i++) {
            cur_sum += nums[i];
            freq[nums[i]] += 1;
        }

        if (freq.size() == k) {
            rst = cur_sum;
        }

        int n = nums.size();
        for (int i = k; i < n; i++) {
            cur_sum += nums[i] - nums[i - k];
            freq[nums[i]] += 1;
            freq[nums[i - k]] -= 1;
            if (freq[nums[i - k]] == 0) {
                freq.erase(nums[i - k]);
            }

            if (freq.size() == k) {
                rst = max(rst, cur_sum);
            }
        }
        return rst;
    }
};
