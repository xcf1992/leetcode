/*
1498. Number of Subsequences That Satisfy the Given Sum Condition
https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/

Given an array of integers nums and an integer target.
Return the number of non-empty subsequences of nums such that
the sum of the minimum and maximum element on it is less or equal than target.

Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: nums = [3,5,6,7], target = 9
Output: 4
Explanation: There are 4 subsequences that satisfy the condition.
[3] -> Min value + max value <= target (3 + 3 <= 9)
[3,5] -> (3 + 5 <= 9)
[3,5,6] -> (3 + 6 <= 9)
[3,6] -> (3 + 6 <= 9)

Example 2:
Input: nums = [3,3,6,8], target = 10
Output: 6
Explanation: There are 6 subsequences that satisfy the condition. (nums can have repeated numbers).
[3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6]

Example 3:
Input: nums = [2,3,3,4,6,7], target = 12
Output: 61
Explanation: There are 63 non-empty subsequences, two of them don't satisfy the condition ([6,7], [7]).
Number of valid subsequences (63 - 2 = 61).

Example 4:
Input: nums = [5,2,4,1,7,6,8], target = 16
Output: 127
Explanation: All non-empty subset satisfy the condition (2^7 - 1) = 127

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
1 <= target <= 10^6
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
#include <climits>

using namespace std;

class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        int result = 0;
        int n = nums.size();
        int mod = 1e9 + 7;

        vector<int> pre = {1};
        for (auto i = pre.size(); i <= n; ++i) {
            pre.push_back((pre.back() << 1) % mod);  // pre calculate 2^n
        }

        sort(nums.begin(), nums.end());
        for (int left = 0; left < n; ++left) {
            int limit = target - nums[left];
            if (limit < nums[left]) {
                continue;
            }
            int right = upper_bound(nums.begin(), nums.end(), limit) - nums.begin();
            result = (result + pre[right - left - 1]) %
                     mod;  // for each number from left + 1, left + 2...right - 1; we have 2 choice pick or not pick
        }
        return result;
    }
};
