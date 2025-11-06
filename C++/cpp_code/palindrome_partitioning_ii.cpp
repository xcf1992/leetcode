/*
https://leetcode.com/problems/palindrome-partitioning-ii/description/
132. Palindrome Partitioning II

Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

Example:
Input: "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        if (n <= 1) {
            return 0;
        }

        vector<vector<int>> isPalindrome(n, vector<int>(n, false));
        vector<int> dp(n, n);  // we need at most n cuts, to cut the string into single letters
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (s[j] == s[i] and (j + 1 >= i - 1 or isPalindrome[j + 1][i - 1])) {
                    isPalindrome[j][i] = true;
                    dp[i] = j == 0 ? 0 : min(dp[i], dp[j - 1] + 1);
                }
            }
        }
        return dp[n - 1];
    }
};