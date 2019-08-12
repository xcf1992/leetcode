/*
594. Longest Harmonious Subsequence
We define a harmounious array as an array where the difference between its maximum value and its minimum value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.

Example 1:

Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].


Note: The length of the input array will not exceed 20,000.
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
    int findLHS(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int minVal = nums[0];
        int maxVal = nums[0];
        int minPos = 0;
        int maxPos = 0;
        int result = 0;
        nums.push_back(INT_MAX);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == minVal + 1) {
                if (minVal == maxVal) {
                    maxVal = nums[i];
                    maxPos = i;
                }
            }
            else {
                if (minVal == maxVal) {
                    minPos = i;
                    maxPos = i;
                    minVal = nums[i];
                    maxVal = nums[i];
                }
                else {
                    result = max(result, i - minPos);
                    minVal = maxVal;
                    minPos = maxPos;
                    i--;
                }
            }
        }
        return result;
    }
};