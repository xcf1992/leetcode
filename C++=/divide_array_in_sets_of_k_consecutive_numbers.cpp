/*
1296. Divide Array in Sets of K Consecutive Numbers
https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/

Given an array of integers nums and a positive integer k,
find whether it's possible to divide this array into sets of k consecutive numbers
Return True if its possible otherwise return False.

Example 1:
Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].

Example 2:
Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].

Example 3:
Input: nums = [3,3,2,2,1,1], k = 3
Output: true

Example 4:
Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= nums.length
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        map<int, int> count;
        for (int num : nums) {
            count[num] += 1;
        }

        for (auto& it : count) {
            int num = it.first;
            int cnt = it.second;
            if (cnt > 0) {
                for (int i = 0; i < k; ++i) {
                    if (count[num + i] < cnt) {
                        return false;
                    }
                    count[num + i] -= cnt;
                }
            }
        }
        return true;
    }
};
