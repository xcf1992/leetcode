/*
131. Palindrome Partitioning
https://leetcode.com/problems/palindrome-partitioning/

Given a string s, partition s such that every substring of the partition is a palindrome.
Return all possible palindrome partitioning of s.

Example:
Input: "aab"
Output:
[
  ["aa","b"],
  ["a","a","b"]
]
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
private:
    void dfs(vector<vector<string>>& results, vector<string> cur, string& s, int start, vector<vector<bool>>& dp) {
        if (start >= s.size()) {
            results.push_back(cur);
            return;
        }

        for (int j = start; j < s.size(); j++)
            if (dp[start][j]) {
                cur.push_back(s.substr(start, j - start + 1));
                dfs(results, cur, s, j + 1, dp);
                cur.pop_back();
            }
    }

public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        if (n == 0) {
            return {};
        }

        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
            if (i + 1 < n and s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
            }
        }

        for (int len = 3; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j] and dp[i + 1][j - 1]) {
                    dp[i][j] = true;
                }
            }
        }

        vector<string> current;
        vector<vector<string>> result;
        dfs(result, current, s, 0, dp);
        return result;
    }
};