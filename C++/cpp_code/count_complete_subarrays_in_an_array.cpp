/*
https://leetcode.com/problems/count-complete-subarrays-in-an-array/description/
2799. Count Complete Subarrays in an Array

You are given an array nums consisting of positive integers.

We call a subarray of an array complete if the following condition is satisfied:

The number of distinct elements in the subarray is equal to the number of distinct elements in the whole array.
Return the number of complete subarrays.

A subarray is a contiguous non-empty part of an array.



Example 1:

Input: nums = [1,3,1,2,2]
Output: 4
Explanation: The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].
Example 2:

Input: nums = [5,5,5,5]
Output: 10
Explanation: The array consists only of the integer 5, so any subarray is complete. The number of subarrays that we can
choose is 10.


Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 2000
*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
using namespace std;

class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> distinct_nums(nums.begin(), nums.end());
        int distinct_cnt = distinct_nums.size();
        unordered_map<int, int> freq;
        int left = 0;
        int right = 0;
        int rst = 0;
        while (right < n) {
            freq[nums[right]] += 1;
            if (freq.size() < distinct_cnt) {
                right += 1;
                continue;
            }

            while (freq.size() >= distinct_cnt) {
                rst += n - right;
                freq[nums[left]] -= 1;
                if (freq[nums[left]] == 0) {
                    freq.erase(nums[left]);
                }
                left += 1;
            }
            right += 1;
        }
        return rst;
    }
};