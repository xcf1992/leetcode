/*
525. Contiguous Array
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.
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
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> diff(n + 1, 0);
        unordered_map<int, int> pos;

        int result = 0;
        for (int i = 0; i < n; i++) {
            diff[i + 1] = diff[i] + (nums[i] == 0 ? -1 : 1);

            if (diff[i + 1] == 0) {
                result = max(result, i + 1);
            }

            if (pos.find(diff[i + 1]) == pos.end()) {
                pos[diff[i + 1]] = i;
            } else {
                result = max(result, i - pos[diff[i + 1]]);
            }
        }
        return result;
    }
};
