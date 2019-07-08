/*
91. Decode Ways
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

/*
DP Solution O(n)
For every ith digit, starting from ith index, either single digit number is valid (>0) or two digit number is valid (<=26),
so number of ways dp[i] = ways for dp[i+1] (if ith single digit is valid, 0 otherwise) + dp[i+2] (if starting from i index 2 &1 digit numbers are valid, 0 otherwise)
dp[i] = dp[i+1] + dp[i+2];
Base condition :: dp[s.len-1] = 1, if last single digit is valid, 0 otherwise.
*/
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n + 1, 0);
        dp[n] = 1;
        dp[n - 1] = s[n - 1] == '0' ? 0 : 1;

        for (int i = n - 2; i >= 0; i--) {
            if (s[i] == '0') {
                continue;
            }
            int num = stoi(s.substr(i, 2));
            dp[i] = num <= 26 ? dp[i + 1] + dp[i + 2] : dp[i + 1];
        }
        return dp[0];
    }
};

class Solution1 {
public:
    int numDecodings(string s) {
        if (s[0] == '0') {
            return 0;
        }
        if (s.size() <= 1) {
            return s.size();
        }

        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= s.size(); i++) {
            int num = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            if (num == 0) {
                return 0;
            }

            if (num < 10) {
                dp[i] = dp[i - 1];
            }
            else if (num == 10 || num == 20) {
                dp[i] = dp[i - 2];
            }
            else if (num <= 26) {
                dp[i] = dp[i - 1] + dp[i - 2];
            }
            else if (num % 10 == 0) {
                return 0;
            }
            else {
                dp[i] = dp[i - 1];
            }
        }

        return dp.back();
    }
};