/*
1262. Greatest Sum Divisible by Three
https://leetcode.com/problems/greatest-sum-divisible-by-three/

Given an array nums of integers,
we need to find the maximum possible sum of elements of the array such that it is divisible by three.

Example 1:
Input: nums = [3,6,5,1,8]
Output: 18
Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).

Example 2:
Input: nums = [4]
Output: 0
Explanation: Since 4 is not divisible by 3, do not pick any number.

Example 3:
Input: nums = [1,2,3,4,4]
Output: 12
Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).

Constraints:
1 <= nums.length <= 4 * 10^4
1 <= nums[i] <= 10^4
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
#include "extra_data_types.hpp"
using namespace std;
/*
Explanation
seen[i] means the current maximum possible sum that sum % 3 = i

Complexity
Time O(N)
Space O(1)

Intuition:
    1.The last maximum possible sum that it is divisible by three could only depends
    on 3 kinds of "subroutines/subproblems":
        1. previous maximum possible sum that it is divisible by three
            preSum % 3 == 0       (example: preSum=12 if lastNum=3)
        2. preSum % 3 == 1       (example: preSum=13 if lastNum=2)
        3. preSum % 3 == 2       (example: preSum=14 if lastNum=1)
    2. This recusion + "subroutines" pattern hints Dynamic Programming

dp state:
    dp[i] = max sum such that the reminder == i when sum / 3
Transition:
    dp_cur[(rem + num) % 3]
        = max(dp_prev[(rem + num) % 3], dp_prev[rem]+num)
        where "rem" stands for reminder for shorter naming
    meaning:
        "Current max sum with reminder 0 or 1 or 2" could be from
        EITHER prevSum with reminder 0 or 1 or 2 consecutively
        OR     prevSum with some reminder "rem" + current number "num"

        Since (dp_prev[rem]+num) % 3 = (rem+num) % 3 = i, we are able to correctly
        update dp[i] for i = 1,2,3 each time
*/
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        vector<int> dp({0, INT_MIN, INT_MIN});
        for (int num : nums) {
            vector<int> temp({0, INT_MIN, INT_MIN});
            for (int i = 0; i < 3; ++i) {
                int rem = (i + num) % 3;
                temp[rem] = max(dp[i] + num, dp[rem]);
            }
            dp = temp;
        }
        return dp[0];
    }
};