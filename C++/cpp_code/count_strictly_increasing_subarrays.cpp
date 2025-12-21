/*
https://leetcode.com/problems/count-strictly-increasing-subarrays/description/
2393. Count Strictly Increasing Subarrays

You are given an array nums consisting of positive integers.

Return the number of subarrays of nums that are in strictly increasing order.

A subarray is a contiguous part of an array.



Example 1:

Input: nums = [1,3,5,4,4,6]
Output: 10
Explanation: The strictly increasing subarrays are the following:
- Subarrays of length 1: [1], [3], [5], [4], [4], [6].
- Subarrays of length 2: [1,3], [3,5], [4,6].
- Subarrays of length 3: [1,3,5].
The total number of subarrays is 6 + 3 + 1 = 10.
Example 2:

Input: nums = [1,2,3,4,5]
Output: 15
Explanation: Every subarray is strictly increasing. There are 15 possible subarrays that we can take.


Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 106
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
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
    long long countSubarrays(vector<int>& nums) {
        long long rst = 0;
        int n = nums.size();
        int left = 0;
        while (left < n) {
            int right = left;
            while (right < n && nums[right] > nums[left]) {
                right += 1;
            }

            long long cnt = right - left;
            rst += cnt * (cnt + 1) / 2;
            left = right;
        }
        return rst;
    }
};