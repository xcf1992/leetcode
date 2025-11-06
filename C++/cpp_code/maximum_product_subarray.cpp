ß /*
152. Maximum Product Subarray
https://leetcode.com/problems/maximum-product-subarray/

Given an integer array nums,
find the contiguous subarray within an array (containing at least one number)
which has the largest product.

Example 1:
Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
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
    int maxProduct(vector<int>& nums) {
        int curMax = nums[0];
        int curMin = nums[0];
        int result = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int newMin = curMin * nums[i];
            int newMax = curMax * nums[i];
            curMax = max(nums[i], max(newMax, newMin));
            curMin = min(nums[i], min(newMax, newMin));
            result = max(curMax, result);
        }
        return result;
    }
};