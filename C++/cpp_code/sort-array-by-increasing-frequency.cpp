/*
1636. Sort Array by Increasing Frequency
https://leetcode.com/problems/sort-array-by-increasing-frequency/

Given an array of integers nums, sort the array in increasing order based on the frequency of the values.
If multiple values have the same frequency, sort them in decreasing order.

Return the sorted array.

Example 1:
Input: nums = [1,1,2,2,2,3]
Output: [3,1,1,2,2,2]
Explanation: '3' has a frequency of 1, '1' has a frequency of 2, and '2' has a frequency of 3.

Example 2:
Input: nums = [2,3,1,3,2]
Output: [1,3,3,2,2]
Explanation: '2' and '3' both have a frequency of 2, so they are sorted in decreasing order.

Example 3:
Input: nums = [-1,1,-6,4,5,-6,1,4,1]
Output: [5,-1,4,4,-6,-6,1,1,1]

Constraints:
1 <= nums.length <= 100
-100 <= nums[i] <= 100
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
#include <cfloat>
#include <stdio.h>
#include <map>
#include <set>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        int cnt[201] = {};
        for (auto n : nums) {
            ++cnt[n + 100];
        }
        sort(begin(nums), end(nums),
             [&](int a, int b) { return cnt[a + 100] == cnt[b + 100] ? a > b : cnt[a + 100] < cnt[b + 100]; });
        return nums;
    }
};