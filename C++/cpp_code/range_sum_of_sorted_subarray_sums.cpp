/*
1508. Range Sum of Sorted Subarray Sums
https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/

Given the array nums consisting of n positive integers.
You computed the sum of all non-empty continous subarrays from the array and then sort them in non-decreasing order,
creating a new array of n * (n + 1) / 2 numbers.

Return the sum of the numbers from index left to index right (indexed from 1),
inclusive, in the new array. Since the answer can be a huge number return it modulo 10^9 + 7.

Example 1:
Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
Output: 13
Explanation: All subarray sums are 1, 3, 6, 10, 2, 5, 9, 3, 7, 4. After sorting them in non-decreasing order we have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 1 to ri = 5 is 1 + 2 + 3 + 3 + 4 = 13.

Example 2:
Input: nums = [1,2,3,4], n = 4, left = 3, right = 4
Output: 6
Explanation: The given array is the same as example 1. We have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 3 to ri = 4 is 3 + 3 = 6.

Example 3:
Input: nums = [1,2,3,4], n = 4, left = 1, right = 10
Output: 50

Constraints:
1 <= nums.length <= 10^3
nums.length == n
1 <= nums[i] <= 100
1 <= left <= right <= n * (n + 1) / 2
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;
/*
The element in priority queue is a pair of integers. The first integer is the nums[i] + ... + nums[j], and the second integer is j+1.

The running time is O(right * lgn) worst case. The real benefit of using priority_queue is that memory usage is O(n).
*/
class Solution {
public:
    int rangeSum(vector<int> &nums, int n, int left, int right) {
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > mqueue;
        for (int i = 0; i < n; i++) {
            mqueue.push({nums[i], i + 1});
        }

        int result = 0;
        int mod = 1e9 + 7;
        for (int i = 1; i <= right; i++) {
            auto p = mqueue.top();
            mqueue.pop();

            if (i >= left) {
                result = (result + p.first) % mod;
            }
            if (p.second < n) {
                p.first += nums[p.second];
                p.second += 1;
                mqueue.push(p);
            }
        }
        return result;
    }
};