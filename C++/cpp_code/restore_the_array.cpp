/*
1416. Restore The Array
https://leetcode.com/problems/restore-the-array/

A program was supposed to print an array of integers.
The program forgot to print whitespaces and the array is printed as a string of digits
and all we know is that all integers in the array were in the range [1, k]
and there are no leading zeros in the array.

Given the string s and the integer k.
There can be multiple ways to restore the array.

Return the number of possible array that can be printed as a string s using the mentioned program.
The number of ways could be very large so return it modulo 10^9 + 7

Example 1:
Input: s = "1000", k = 10000
Output: 1
Explanation: The only possible array is [1000]

Example 2:
Input: s = "1000", k = 10
Output: 0
Explanation: There cannot be an array that was printed this way and has all integer >= 1 and <= 10.

Example 3:
Input: s = "1317", k = 2000
Output: 8
Explanation: Possible arrays are [1317],[131,7],[13,17],[1,317],[13,1,7],[1,31,7],[1,3,17],[1,3,1,7]

Example 4:
Input: s = "2020", k = 30
Output: 1
Explanation: The only possible array is [20,20]. [2020] is invalid because 2020 > 30. [2,020] is ivalid because 020
contains leading zeros.

Example 5:
Input: s = "1234567890", k = 90
Output: 34

Constraints:
1 <= s.length <= 10^5.
s consists of only digits and doesn't contain leading zeros.
1 <= k <= 10^9.
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
#include <map>
using namespace std;

class Solution {
private:
    int mod = 1e9 + 7;

    int dfs(string& s, long k, int i, vector<int>& dp) {
        if (i == s.size()) {
            return 1;  // base case -> Found a valid way
        }

        if (s[i] == '0') {
            return 0;
            // all numbers are in range [1, k] and there are no leading zeros -> So numbers starting with 0 mean
            // invalid!
        }

        if (dp[i] != -1) {
            return dp[i];
        }

        dp[i] = 0;
        long num = 0;
        for (int j = i; j < s.size(); j++) {
            num = num * 10 + s[j] - '0';  // num is the value of the substring s[i..j]
            if (num > k) {
                break;  // num must be in range [1, k]
            }
            dp[i] += dfs(s, k, j + 1, dp);
            dp[i] %= mod;
        }
        return dp[i];
    }

public:
    int numberOfArrays(string s, int k) {
        vector<int> dp(s.size(), -1);  // dp[i] is number of ways to print valid arrays from string s start at i
        return dfs(s, k, 0, dp);
    }
};