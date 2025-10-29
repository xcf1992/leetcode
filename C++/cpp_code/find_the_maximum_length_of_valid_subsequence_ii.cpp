/*
https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/ Maximum Frequency After Subarray Operation
3202. Find the Maximum Length of Valid Subsequence II
You are given an integer array nums and a positive integer k.
A subsequence sub of nums with length x is called valid if it satisfies:

(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.
Return the length of the longest valid subsequence of nums.


Example 1:

Input: nums = [1,2,3,4,5], k = 2

Output: 5

Explanation:

The longest valid subsequence is [1, 2, 3, 4, 5].

Example 2:

Input: nums = [1,4,2,3,1,4], k = 3

Output: 4

Explanation:

The longest valid subsequence is [1, 4, 1, 4].



Constraints:

2 <= nums.length <= 10^3
1 <= nums[i] <= 10^7
1 <= k <= 10^3
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        vector<vector<int>> dp(k, vector<int>(k, 0));
        int res = 0;
        for (int num : nums) {
            num %= k;
            for (int prev = 0; prev < k; ++prev) {
                dp[prev][num] = dp[num][prev] + 1;
                res = max(res, dp[prev][num]);
            }
        }
        return res;
    }
};

class Solution1 {
public:
    int maximumLength(vector<int> &nums, int k) {
        // Step 1: Create a 2D DP table to track remainder transitions
        vector<vector<int> > dp(k, vector<int>(k, 0)); // dp[prev_rem][curr_rem]
        int result = 0;

        // Step 2: Loop through each number in the array
        for (int num: nums) {
            int cur_rem = num % k;

            // Step 3: Try to extend previously formed sequences
            for (int prev_rem = 0; prev_rem < k; ++prev_rem) {
                // Step 4: Extend the sequence from (current_rem → prev_rem) to (prev_rem → current_rem)
                dp[prev_rem][cur_rem] = dp[cur_rem][prev_rem] + 1;

                // Step 5: Update the maximum length found so far
                result = max(result, dp[prev_rem][cur_rem]);
            }
        }

        // Step 6: Return the result
        return result;
    }
};
