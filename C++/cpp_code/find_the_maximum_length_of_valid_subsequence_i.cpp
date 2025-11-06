/*
https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/description/
3201. Find the Maximum Length of Valid Subsequence I

You are given an integer array nums.
A subsequence sub of nums with length x is called valid if it satisfies:

(sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.
Return the length of the longest valid subsequence of nums.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the
order of the remaining elements.



Example 1:

Input: nums = [1,2,3,4]

Output: 4

Explanation:

The longest valid subsequence is [1, 2, 3, 4].

Example 2:

Input: nums = [1,2,1,1,2,1,2]

Output: 6

Explanation:

The longest valid subsequence is [1, 2, 1, 2, 1, 2].

Example 3:

Input: nums = [1,3]

Output: 2

Explanation:

The longest valid subsequence is [1, 3].



Constraints:

2 <= nums.length <= 2 * 105
1 <= nums[i] <= 10^7
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
    int maximumLength(vector<int>& nums) {
        int even_cnt = 0;
        int odd_cnt = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % 2 == 0) {
                even_cnt += 1;
            } else {
                odd_cnt += 1;
            }
        }

        int even_dp = 0;
        int odd_dp = 0;
        for (int cur : nums) {
            if (cur % 2 == 0) {
                even_dp = max(even_dp, odd_dp + 1);
            } else {
                odd_dp = max(odd_dp, even_dp + 1);
            }
        }
        return max(max(even_cnt, odd_cnt), max(even_dp, odd_dp));
    }
};
