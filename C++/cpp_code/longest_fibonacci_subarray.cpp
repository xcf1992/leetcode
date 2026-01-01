/*
https://leetcode.com/problems/longest-fibonacci-subarray/description/
3708. Longest Fibonacci Subarray

You are given an array of positive integers nums.

A Fibonacci array is a contiguous sequence whose third and subsequent terms each equal the sum of the two preceding
terms.

Return the length of the longest Fibonacci subarray in nums.

Note: Subarrays of length 1 or 2 are always Fibonacci.



Example 1:

Input: nums = [1,1,1,1,2,3,5,1]

Output: 5

Explanation:

The longest Fibonacci subarray is nums[2..6] = [1, 1, 2, 3, 5].

[1, 1, 2, 3, 5] is Fibonacci because 1 + 1 = 2, 1 + 2 = 3, and 2 + 3 = 5.

Example 2:

Input: nums = [5,2,7,9,16]

Output: 5

Explanation:

The longest Fibonacci subarray is nums[0..4] = [5, 2, 7, 9, 16].

[5, 2, 7, 9, 16] is Fibonacci because 5 + 2 = 7, 2 + 7 = 9, and 7 + 9 = 16.

Example 3:

Input: nums = [1000000000,1000000000,1000000000]

Output: 2

Explanation:

The longest Fibonacci subarray is nums[1..2] = [1000000000, 1000000000].

[1000000000, 1000000000] is Fibonacci because its length is 2.



Constraints:

3 <= nums.length <= 105
1 <= nums[i] <= 109
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

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) {
            return n;
        }

        int left = 0;
        int cur = 2;
        int rst = 2;
        while (cur < n) {
            if (nums[cur] == nums[cur - 1] + nums[cur - 2]) {
                cur += 1;
                rst = max(rst, cur - left);
                continue;
            }

            rst = max(rst, cur - left);
            left = cur - 1;
        }
        return rst;
    }
};