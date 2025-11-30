/*
1246. Palindrome Removal
https://leetcode.com/problems/palindrome-removal/

Given an integer array arr,
in one move you can select a palindromic subarray arr[i], arr[i+1], ..., arr[j] where i <= j,
and remove that subarray from the given array.
Note that after removing a subarray,
the elements on the left and on the right of that subarray move to fill the gap left by the removal.

Return the minimum number of moves needed to remove all numbers from the array.

Example 1:
Input: arr = [1,2]
Output: 2

Example 2:
Input: arr = [1,3,4,1,5]
Output: 3
Explanation: Remove [4] then remove [1,3,1] then remove [5].

Constraints:
1 <= arr.length <= 100
1 <= arr[i] <= 20
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
#include <climits>
using namespace std;

class Solution {
public:
    int minimumMoves(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) {
            return n;
        }

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int len = 1; len <= n; ++len) {
            for (int i = 0, j = len - 1; j < n; ++i, ++j) {
                if (len == 1) {
                    dp[i][j] = 1;
                    continue;
                }

                dp[i][j] = 1 + dp[i + 1][j];
                if (arr[i] == arr[i + 1]) {
                    dp[i][j] = min(dp[i][j], 1 + dp[i + 2][j]);
                }
                for (int k = i + 2; k <= j; ++k) {
                    if (arr[i] == arr[k]) {
                        dp[i][j] = min(dp[i][j], dp[i + 1][k - 1] + dp[k + 1][j]);
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};