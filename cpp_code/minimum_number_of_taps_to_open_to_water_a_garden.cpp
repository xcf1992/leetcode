/*
1326. Minimum Number of Taps to Open to Water a Garden
https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/

There is a one-dimensional garden on the x-axis.
The garden starts at the point 0 and ends at the point n.
(i.e The length of the garden is n).

There are n + 1 taps located at points [0, 1, ..., n] in the garden.

Given an integer n and an integer array ranges of length n + 1
where ranges[i] (0-indexed) means the i-th tap can water the area [i - ranges[i], i + ranges[i]]
if it was open.

Return the minimum number of taps that should be open to water the whole garden,
If the garden cannot be watered return -1.

Example 1:
Input: n = 5, ranges = [3,4,1,1,0,0]
Output: 1
Explanation: The tap at point 0 can cover the interval [-3,3]
The tap at point 1 can cover the interval [-3,5]
The tap at point 2 can cover the interval [1,3]
The tap at point 3 can cover the interval [2,4]
The tap at point 4 can cover the interval [4,4]
The tap at point 5 can cover the interval [5,5]
Opening Only the second tap will water the whole garden [0,5]

Example 2:
Input: n = 3, ranges = [0,0,0,0]
Output: -1
Explanation: Even if you activate all the four taps you cannot water the whole garden.

Example 3:
Input: n = 7, ranges = [1,2,1,0,2,1,0,1]
Output: 3

Example 4:
Input: n = 8, ranges = [4,0,0,0,0,0,0,0,4]
Output: 2

Example 5:
Input: n = 8, ranges = [4,0,0,0,4,0,0,0,4]
Output: 1

Constraints:
1 <= n <= 10^4
ranges.length == n + 1
0 <= ranges[i] <= 100
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
Solution 1: Brute Force DP
dp[i] is the minimum number of taps to water [0, i].
Initialize dp[i] with max = n + 2
dp[0] = [0] as we need no tap to water nothing.

Find the leftmost point of garden to water with tap i.
Find the rightmost point of garden to water with tap i.
We can water [left, right] with onr tap,
and water [0, left - 1] with dp[left - 1] taps.

Complexity
Time O(NR), where R = ranges[i] <= 100
Space O(N)

same question as 1024 video stitching
*/
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> dp(n + 1, n + 2);
        dp[0] = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = max(i - ranges[i] + 1, 0); j <= min(i + ranges[i], n); ++j) {
                dp[j] = min(dp[j], dp[max(0, i - ranges[i])] + 1);
            }
        }
        return dp[n]  < n + 2 ? dp[n] : -1;
    }
};
