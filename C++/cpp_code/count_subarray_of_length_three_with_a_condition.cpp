/*
https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/description/
3392. Count Subarrays of Length Three With a Condition

Given an integer array nums, return the number of subarrays of length 3 such that the sum of the first and third numbers
equals exactly half of the second number.



Example 1:

Input: nums = [1,2,1,4,1]

Output: 1

Explanation:

Only the subarray [1,4,1] contains exactly 3 elements where the sum of the first and third numbers equals half the
middle number.

Example 2:

Input: nums = [1,1,1]

Output: 0

Explanation:

[1,1,1] is the only subarray of length 3. However, its first and third numbers do not add to half the middle number.



Constraints:

3 <= nums.length <= 100
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
#include <climits>
#include <map>
using namespace std;

class Solution {
public:
    int countSubarrays(vector<int>& nums) {
        int rst = 0;
        int n = nums.size();
        for (int i = 1; i <= n - 2; i++) {
            if (nums[i] == ((nums[i - 1] + nums[i + 1]) << 1)) {
                rst += 1;
            }
        }
        return rst;
    }
};