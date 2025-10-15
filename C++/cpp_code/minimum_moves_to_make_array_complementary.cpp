/*
1674. Minimum Moves to Make Array Complementary
https://leetcode.com/problems/minimum-moves-to-make-array-complementary/

You are given an integer array nums of even length n and an integer limit.
In one move, you can replace any integer from nums with another integer between 1 and limit, inclusive.

The array nums is complementary if for all indices i (0-indexed),
nums[i] + nums[n - 1 - i] equals the same number.
For example, the array [1,2,3,4] is complementary because for all indices i,
nums[i] + nums[n - 1 - i] = 5.

Return the minimum number of moves required to make nums complementary.

Example 1:
Input: nums = [1,2,4,3], limit = 4
Output: 1
Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
nums[0] + nums[3] = 1 + 3 = 4.
nums[1] + nums[2] = 2 + 2 = 4.
nums[2] + nums[1] = 2 + 2 = 4.
nums[3] + nums[0] = 3 + 1 = 4.
Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.

Example 2:
Input: nums = [1,2,2,1], limit = 2
Output: 2
Explanation: In 2 moves, you can change nums to [2,2,2,2]. You cannot change any number to 3 since 3 > limit.

Example 3:
Input: nums = [1,2,1,2], limit = 2
Output: 0
Explanation: nums is already complementary.

Constraints:
n == nums.length
2 <= n <= 105
1 <= nums[i] <= limit <= 105
n is even.
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
/*
If we want to make the nums complementary,
having all the pairs A = nums[i], B = nums[n - 1 - i] with A + B = T.
Considering a pair A = nums[i], B = nums[n - 1 - i],
there are 5 different situation for every such pair (A, B), given different target T.

2 <= T < min(A, B) + 1, we need 2 operations to make both A, B smaller
min(A, B) + 1 <= T < A + B, we need 1 operation to make the larger one out of A and B smaller
T = A + B, we need 0 operation
A + B < T < max(A, B) + limit, we need 1 operation to make the smaller one out of A and B larger
max(A, B) + limit < T <= 2 * limit, we need 2 operation to make both A, B larger
We calculate the boundary for each pair (A, B) and note down the corresponding operation changes as delta.
delta[i] = x means we need x more operations when target T change from i - 1 to i.
*/
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int N = nums.size();
        vector<int> memo(limit * 2 + 2, 0);
        for (int i = 0; i < N / 2; ++i) {
            int l = nums[i];
            int r = nums[N - 1 - i];
            --memo[min(l, r) + 1];
            --memo[l + r];
            ++memo[l + r + 1];
            ++memo[max(l, r) + limit + 1];
        }
        int ans = N, curr = N;
        for (int i = 2; i <= limit*2; ++i) {
            curr += memo[i];
            ans = min(ans, curr);
        }
        return ans;
    }
};
