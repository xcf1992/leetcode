/*
45. Jump Game II

Given an array of non-negative integers,
you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.

Example:
Input: [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
Jump 1 step from index 0 to 1, then 3 steps to the last index.

Note:
You can assume that you can always reach the last index.
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
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return 0;
        }

        int result = 1;
        int curMax = nums[0];
        int lastMax = nums[0];
        for (int i = 1; i < n; ++i) {
            if (i > lastMax) {
                lastMax = curMax;
                result += 1;
            }
            curMax = max(curMax, i + nums[i]);
        }
        return result;
    }
};
