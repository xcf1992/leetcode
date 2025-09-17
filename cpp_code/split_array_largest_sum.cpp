/*
410. Split Array Largest Sum
https://leetcode.com/problems/split-array-largest-sum/

Given an array which consists of non-negative integers and an integer m,
you can split the array into m non-empty continuous subarrays.
Write an algorithm to minimize the largest sum among these m subarrays.

Note:
If n is the length of array, assume the following constraints are satisfied:
1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)

Examples:
Input:
nums = [7,2,5,10,8]
m = 2
Output:
18
Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
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
using namespace std;
/*
If we can find a splitting method that ensures the maximum largest subarray sum will not exceed a value x,
then we can also find a splitting method that ensures the maximum largest subarray sum will not exceed any value y
that is greater than x.

binary search
#define LL long long
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        LL l = 0, r = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            r += nums[i];
            if (l < nums[i]) {
                l = nums[i];
            }
        }
        LL ans =  r;
        while (l <= r) {
            LL mid = (l + r) >> 1;
            LL sum = 0;
            int cnt = 1;
            for (int i = 0; i < n; i++) {
                if (sum + nums[i] > mid) {
                    cnt ++;
                    sum = nums[i];
                } else {
                    sum += nums[i];
                }
            }
            if (cnt <= m) {
                ans = min(ans, mid);
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};
*/
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<vector<long>> dp(m + 1, vector<long>(n + 1, INT_MAX));
        dp[0][0] = 0;
        for (int i = 1; i <= m; i++) {
            dp[i][1] = nums[0];
            dp[i][0] = 0;
        }
        for (int j = 1; j <= n; j++) {
            dp[1][j] = dp[1][j - 1] + nums[j - 1];
        }

        for (int i = 2; i <= m; i++) {
            for (int j = i; j <= n; j++) {
                for (int k = 0; k < j; k++) {
                    dp[i][j] = min(dp[i][j], max(dp[i - 1][k], dp[1][j] - dp[1][k]));
                }
            }
        }
        return dp[m][n];
    }
};
