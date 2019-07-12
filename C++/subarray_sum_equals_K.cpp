/*
560. Subarray Sum Equals K
Given an array of integers and an integer k,
you need to find the total number of continuous subarrays whose sum equals to k.

Example 1:
Input:nums = [1,1,1], k = 2
Output: 2
Note:
The length of the array is in range [1, 20,000].
The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].
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
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> preSum;
        preSum[0] = 1;
        int sum = 0;
        int result = 0;
        for (int num : nums) {
            sum += num;
            if (preSum.find(sum - k) != preSum.end()) {
                result += preSum[sum - k];
            }
            preSum[sum] += 1;
        }
        return result;
    }
};
