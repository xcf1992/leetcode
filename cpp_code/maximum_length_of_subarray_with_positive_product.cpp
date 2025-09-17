/*
1567. Maximum Length of Subarray With Positive Product
https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/

Given an array of integers nums,
find the maximum length of a subarray where the product of all its elements is positive.
A subarray of an array is a consecutive sequence of zero or more values taken out of that array.
Return the maximum length of a subarray with positive product.

Example 1:
Input: nums = [1,-2,-3,4]
Output: 4
Explanation: The array nums already has a positive product of 24.

Example 2:
Input: nums = [0,1,-2,-3,-4]
Output: 3
Explanation: The longest subarray with positive product is [1,-2,-3] which has a product of 6.
Notice that we cannot include 0 in the subarray since that'll make the product 0 which is not positive.

Example 3:
Input: nums = [-1,-2,-3,0,1]
Output: 2
Explanation: The longest subarray with positive product is [-1,-2] or [-2,-3].

Example 4:
Input: nums = [-1,2]
Output: 1

Example 5:
Input: nums = [1,2,3,5,-6,4,0,10]
Output: 4

Constraints:
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
Accepted
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
using namespace std;

class Solution {
public:
    int getMaxLen(vector<int> nums) {
        int framestart = -1, firstneg = -2, res = 0, neg = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                neg = 0;
                framestart = i;
                firstneg = -2;
                continue;
            }

            if (nums[i] < 0) {
                neg++;  // number of negatives in  current frame means (frame excluding zero)
            }
            if (neg == 1 && firstneg == -2) {
                firstneg = i;   // init firstneg cnt neg;
            }
            if (neg % 2 == 0) {
                res = max(res, i - framestart);  //if curr cnt neg is framestart;
            }
            else {
                res = max(res, i - firstneg);  // first firstneg after last zero;
            }
        }
        return res;
    }
};
