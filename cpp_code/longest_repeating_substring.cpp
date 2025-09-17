/*
1062. Longest Repeating Substring
https://leetcode.com/problems/longest-repeating-substring/

Given a string S, find out the length of the longest repeating substring(s).
Return 0 if no repeating substring exists.

Example 1:
Input: "abcd"
Output: 0
Explanation: There is no repeating substring.

Example 2:
Input: "abbaba"
Output: 2
Explanation: The longest repeating substrings are "ab" and "ba", each of which occurs twice.

Example 3:
Input: "aabcaabdaab"
Output: 3
Explanation: The longest repeating substring is "aab", which occurs 3 times.

Example 4:
Input: "aaaaa"
Output: 4
Explanation: The longest repeating substring is "aaaa", which occurs twice.

Note:
The string S consists of only lowercase English letters from 'a' - 'z'.
1 <= S.length <= 1500
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
#include <map>
#include <numeric>
using namespace std;

//dp[i][j] means # of repeated chars for substrings ending at i and j
class Solution {
public:
    int longestRepeatingSubstring(string S) {
        int n = S.size();
        int result = 0;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) { // j should be different from i
                if (S[i - 1] == S[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    result = max(result, dp[i][j]);
                }
            }
        }
        return result;
    }
};

// https://stackoverflow.com/questions/711770/fast-implementation-of-rolling-hash
// wrong answer "aaabaabbbaaabaabbaabbbabbbaaaabbaaaaaabbbaabbbbbbbbbaaaabbabbaba"
class Solution2 {
private:
    bool findRepeat(string S, int len) {
        unordered_set<long long> visited;
        size_t p = 113;
        size_t mod = 1e9 + 7;

        long long value = 0;
        long long power = 1;
        for (int i = 0; i < len; ++i) {
            value = (value * p + S[i]) % mod;
            power = (power * p) % mod;
        }

        visited.insert(value);
        for (int i = len; i < S.size(); ++i) {
            value = (value * p + S[i]) % mod;
            value = value - power * S[i - len];
            while (value < 0) {
                value += mod;
            }
            value %= mod;
            if (visited.find(value) != visited.end()) {
                return true;
            }
        }
        return false;
    }
public:
    int longestRepeatingSubstring(string S) {
        int n = S.size();
        if (n <= 1) {
            return 0;
        }

        for (int len = n - 1; len >= 1; --len) {
            if (findRepeat(S, len)) {
                return len;
            }
        }
        return 0;
    }
};

// TLE
class Solution1 {
public:
    int longestRepeatingSubstring(string S) {
        int n = S.size();
        if (n <= 1) {
            return 0;
        }

        for (int len = n - 1; len >= 0; --len) {
            unordered_set<string> visited;
            for (int i = 0; i <= n - len; ++i) {
                string sub = S.substr(i, len);
                if (visited.find(sub) != visited.end()) {
                    return len;
                }
                visited.insert(sub);
            }
        }
        return 0;
    }
};
