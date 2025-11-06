/*
1312. Minimum Insertion Steps to Make a String Palindrome
https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

Given a string s.
In one step you can insert any character at any index of the string.

Return the minimum number of steps to make s palindrome.
A Palindrome String is one that reads the same backward as well as forward.

Example 1:
Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we don't need any insertions.

Example 2:
Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".

Example 3:
Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".

Example 4:
Input: s = "g"
Output: 0

Example 5:
Input: s = "no"
Output: 1

Constraints:
1 <= s.length <= 500
All characters of s are lower case English letters.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;
/*
Intuition
Split the string s into to two parts,
and we try to make them symmetrical by adding letters.

The more common symmetrical subsequence they have,
the less letters we need to add.

Now we change the problem to find the length of longest common sequence.
This is a typical dynamic problem.

Explanation
Step1.
Initialize dp[n+1][n+1],
where dp[i][j] means the length of longest common sequence between
i first letters in s1 and j first letters in s2.

Step2.
Find the the longest common sequence between s1 and s2,
where s1 = s and s2 = reversed(s)

Step3.
return n - dp[n][n]

Complexity
Time O(N^2)
Space O(N^2)
*/
class Solution1 {  // bottom up dp
public:
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i + 1][j + 1] = s[i] == s[n - 1 - j] ? dp[i][j] + 1 : max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
        return n - dp[n][n];
    }
};

class Solution {  // top down dfs with memo
private:
    int dfs(string& s, int i, int j, vector<vector<int>>& memo) {
        if (i >= j) {
            return 0;
        }

        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        memo[i][j] =
                s[i] == s[j] ? dfs(s, i + 1, j - 1, memo) : 1 + min(dfs(s, i + 1, j, memo), dfs(s, i, j - 1, memo));
        return memo[i][j];
    }

public:
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int>> memo(
                n, vector<int>(n, -1));  // memo[i][j] stores the length shortest non-palindrome subsequence of s[i..j]
        return dfs(s, 0, n - 1, memo);
    }
};
