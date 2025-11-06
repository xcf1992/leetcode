/*
300. Longest Increasing Subsequence

Given an unsorted array of integers,
find the length of longest increasing subsequence.

Example:
Input: [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

Note:
There may be more than one LIS combination, it is only necessary for you to return the length.
Your algorithm should run in O(n2) complexity.

Follow up:
Could you improve it to O(n log n) time complexity?
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
/*
https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
Basically we are trying to log longest increasing subsequence in lis
if current num is bigger then current sequence we push it to the back
if any number in current lis is bigger than current num we replace it with current num
cause the size of lis is non-shrinking, which means it will always be the length of longest increasing subsequnce we
ever seen so by replacing internal element with current num(which is smaller), we hope we can longer sequence after
that.
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return n;
        }

        vector<int> lis;
        for (int num : nums) {
            auto it = lower_bound(lis.begin(), lis.end(), num);
            if (it == lis.end()) {
                lis.push_back(num);
            } else {
                *it = num;
            }
        }
        return lis.size();
    }
};

class Solution1 {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return n;
        }

        vector<int> dp(n, 1);
        int result = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            result = max(result, dp[i]);
        }
        return result;
    }
};