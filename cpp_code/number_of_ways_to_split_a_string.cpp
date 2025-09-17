/*
1573. Number of Ways to Split a String
https://leetcode.com/problems/number-of-ways-to-split-a-string/

Given a binary string s (a string consisting only of '0's and '1's),
we can split s into 3 non-empty strings s1, s2, s3 (s1+ s2+ s3 = s).

Return the number of ways s can be split such that the number of characters '1' is the same in s1, s2, and s3.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: s = "10101"
Output: 4
Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
"1|010|1"
"1|01|01"
"10|10|1"
"10|1|01"

Example 2:
Input: s = "1001"
Output: 0

Example 3:
Input: s = "0000"
Output: 3
Explanation: There are three ways to split s in 3 parts.
"0|0|00"
"0|00|0"
"00|0|0"

Example 4:
Input: s = "100100010100110"
Output: 12

Constraints:
s[i] == '0' or s[i] == '1'
3 <= s.length <= 10^5
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
#include <cfloat>
#include <stdio.h>
#include <map>
using namespace std;

class Solution {
public:
    int numWays(string s) {
        int count1 = 0;
        long long n = s.size();
        int mod = 1e9 + 7;
        for (char c : s) {
            count1 += c - '0';
        }
        if (count1 % 3 != 0) {
            return 0;
        }
        if (count1 == 0) {
            long long result = ((n - 1) * (n - 2) / 2) % mod;
            return result;
        }

        int idx1 = -1;
        int idx2 = -1;
        int cur = 0;
        long long gap1 = -1;
        long long gap2 = -1;
        for (int i = 0; i < n; ++i) {
            cur += s[i] - '0';
            if (cur == count1 / 3 and idx1 == -1) {
                idx1 = i;
            }
            if (cur == 1 + count1 / 3 and gap1 == -1) {
                gap1 = i - idx1 - 1;
            }
            if (cur == 2 * count1 / 3 and idx2 == -1) {
                idx2 = i;
            }
            if (cur == 1 + 2 * count1 / 3 and gap2 == -1) {
                gap2 = i - idx2 - 1;
            }
        }
        long long result = ((gap1 + 1) % mod) * ((gap2 + 1) % mod) % mod;
        return result % mod;
    }
};
