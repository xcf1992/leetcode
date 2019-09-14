/*
368. Largest Divisible Subset
https://leetcode.com/problems/largest-divisible-subset/

Given a set of distinct positive integers,
find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 OR Sj % Si = 0.

If there are multiple solutions, return any subset is fine.

Example 1:
nums: [1,2,3]
Result: [1,2] (of course, [1,3] will also be ok)

Example 2:
nums: [1,2,4,8]
Result: [1,2,4,8]
*/
#include <iostream>
#include <sstream>
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
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<int> dp(n, 1);
        vector<int> pre(n, -1);
        int maxCount = 0;
        int index = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) if (nums[i] % nums[j] == 0 and dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                pre[i] = j;
            }
            if (dp[i] > maxCount) {
                maxCount = dp[i];
                index = i;
            }
        }

        vector<int> result;
        for (int i = index; i != -1; i = pre[i]) {
            result.push_back(nums[i]);
        }
        return result;
    }
};
