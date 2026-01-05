/*
https://leetcode.com/problems/minimum-array-sum/description/
3366. Minimum Array Sum

You are given an integer array nums and three integers k, op1, and op2.

You can perform the following operations on nums:

Operation 1: Choose an index i and divide nums[i] by 2, rounding up to the nearest whole number. You can perform this
operation at most op1 times, and not more than once per index. Operation 2: Choose an index i and subtract k from
nums[i], but only if nums[i] is greater than or equal to k. You can perform this operation at most op2 times, and not
more than once per index. Note: Both operations can be applied to the same index, but at most once each.

Return the minimum possible sum of all elements in nums after performing any number of operations.



Example 1:

Input: nums = [2,8,3,19,3], k = 3, op1 = 1, op2 = 1

Output: 23

Explanation:

Apply Operation 2 to nums[1] = 8, making nums[1] = 5.
Apply Operation 1 to nums[3] = 19, making nums[3] = 10.
The resulting array becomes [2, 5, 3, 10, 3], which has the minimum possible sum of 23 after applying the operations.
Example 2:

Input: nums = [2,4,3], k = 3, op1 = 2, op2 = 1

Output: 3

Explanation:

Apply Operation 1 to nums[0] = 2, making nums[0] = 1.
Apply Operation 1 to nums[1] = 4, making nums[1] = 2.
Apply Operation 2 to nums[2] = 3, making nums[2] = 0.
The resulting array becomes [1, 2, 0], which has the minimum possible sum of 3 after applying the operations.


Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 105
0 <= k <= 105
0 <= op1, op2 <= nums.length
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
using namespace std;

class Solution {
public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        int n = nums.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(op1 + 1, vector<int>(op2 + 1, INT_MAX)));
        dp[0][0][0] = 0;

        for (int i = 0; i < n; i++) {
            for (int o1 = 0; o1 <= op1; o1++) {
                for (int o2 = 0; o2 <= op2; o2++) {
                    int cur = dp[i][o1][o2];
                    if (cur >= INT_MAX) {
                        continue;
                    }

                    dp[i + 1][o1][o2] = min(dp[i + 1][o1][o2], cur + nums[i]);
                    if (o1 < op1) {
                        dp[i + 1][o1 + 1][o2] = min(dp[i + 1][o1 + 1][o2], cur + (nums[i] + 1) / 2);
                    }

                    if (o2 < op2 && nums[i] >= k) {
                        dp[i + 1][o1][o2 + 1] = min(dp[i + 1][o1][o2 + 1], cur + nums[i] - k);
                    }

                    if (o1 < op1 && o2 < op2 && (nums[i] + 1) / 2 >= k) {
                        dp[i + 1][o1 + 1][o2 + 1] = min(dp[i + 1][o1 + 1][o2 + 1], cur + (nums[i] + 1) / 2 - k);
                    }

                    if (nums[i] >= k && o1 < op1 && o2 < op2) {
                        dp[i + 1][o1 + 1][o2 + 1] = min(dp[i + 1][o1 + 1][o2 + 1], cur + (nums[i] - k + 1) / 2);
                    }
                }
            }
        }

        int rst = INT_MAX;
        for (int o1 = 0; o1 <= op1; o1++) {
            for (int o2 = 0; o2 <= op2; o2++) {
                rst = min(rst, dp[n][o1][o2]);
            }
        }
        return rst;
    }
};