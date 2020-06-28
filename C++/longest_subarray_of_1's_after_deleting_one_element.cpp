/*
1493. Longest Subarray of 1's After Deleting One Element
https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/

Given a binary array nums, you should delete one element from it.
Return the size of the longest non-empty subarray containing only 1's in the resulting array.
Return 0 if there is no such subarray.

Example 1:
Input: nums = [1,1,0,1]
Output: 3
Explanation: After deleting the number in position 2, [1,1,1] contains 3 numbers with value of 1's.

Example 2:
Input: nums = [0,1,1,1,0,1,1,0,1]
Output: 5
Explanation: After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest subarray with value of 1's is [1,1,1,1,1].

Example 3:
Input: nums = [1,1,1]
Output: 2
Explanation: You must delete one element.

Example 4:
Input: nums = [1,1,0,0,1,1,1,0,1]
Output: 4

Example 5:
Input: nums = [0,0,0]
Output: 0

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
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
#include <set>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int result = 1;
        int left = 0;
        int right = 0;
        int change = 1;
        int n = nums.size();
        while (right < n) {
            while (right < n) {
                if (nums[right] == 1) {
                    right += 1;
                    continue;
                }

                if (change == 1) {
                    change = 0;
                    right += 1;
                    continue;
                }
                break;
            }

            result = max(result, right - left);
            while (left < right and change == 0) {
                if (nums[left] == 0) {
                    change += 1;
                }
                left += 1;
            }
        }
        return max(result, right - left) - 1;
    }
};
