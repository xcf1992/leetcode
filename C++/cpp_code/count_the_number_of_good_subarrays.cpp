/*
https://leetcode.com/problems/count-the-number-of-good-subarrays/description/
2537. Count the Number of Good Subarrays

Given an integer array nums and an integer k, return the number of good subarrays of nums.

A subarray arr is good if there are at least k pairs of indices (i, j) such that i < j and arr[i] == arr[j].

A subarray is a contiguous non-empty sequence of elements within an array.



Example 1:

Input: nums = [1,1,1,1,1], k = 10
Output: 1
Explanation: The only good subarray is the array nums itself.
Example 2:

Input: nums = [3,1,4,3,2,2,4], k = 2
Output: 4
Explanation: There are 4 different good subarrays:
- [3,1,4,3,2,2] that has 2 pairs.
- [3,1,4,3,2,2,4] that has 3 pairs.
- [1,4,3,2,2,4] that has 2 pairs.
- [4,3,2,2,4] that has 2 pairs.


Constraints:

1 <= nums.length <= 105
1 <= nums[i], k <= 109
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int n = nums.size();
        long long rst = 0;
        int pair_cnt = 0;
        int right = -1;
        for (int left = 0; left < n; left++) {
            while (pair_cnt < k && right + 1 < n) {
                right += 1;
                pair_cnt += freq[nums[right]];
                freq[nums[right]] += 1;
            }

            if (pair_cnt >= k) {
                rst += n - right;
            }

            freq[nums[left]] -= 1;
            pair_cnt -= freq[nums[left]];
        }
        return rst;
    }
};