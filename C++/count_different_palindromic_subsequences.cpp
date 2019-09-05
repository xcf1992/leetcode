/*
 730. Count Different Palindromic Subsequences
 Given a string S, find the number of different non-empty palindromic subsequences in S,
 and return that number modulo 10^9 + 7.

 A subsequence of a string S is obtained by deleting 0 or more characters from S.

 A sequence is palindromic if it is equal to the sequence reversed.

 Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.

 Example 1:
 Input:
 S = 'bccb'
 Output: 6
 Explanation:
 The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
 Note that 'bcb' is counted only once, even though it occurs twice.
 Example 2:
 Input:
 S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
 Output: 104860361
 Explanation:
 There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.
 Note:

 The length of S will be in the range [1, 1000].
 Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.
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
#include <set>
#include <numeric>
using namespace std;

/*
 I am not able to pass this question one time but struggle a lot in the basic test cases like "a", "aa", "aaa", "aba", "aabb".
 Those test cases help my early rough idea to be flawless.
 The basic idea of DP is easy to understand,
 I maintain DP[i][j] to record in substring from i to j(included),
 the number of palindrome without duplicate.

 Then we consider two cases of the DP equation:
 when s.charAt(i) != s.charAt(j):
 dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];

 When s.charAt(i) == s.charAt(j):
 the situation get much more complex and I fix a lot the wrong answers.
 I have comment the branches where which kind of test cases are considered.
*/
class Solution {
private:
    int MOD = 1e9 + 7;

    void update(int i, int j, vector<vector<int>>& dp, string& S) {
        if (S[i] != S[j]) {
            dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];
            return;
        }

        int left = i + 1;
        int right = j - 1;
        while (left <= right and S[left] != S[i]) {
            left += 1;
        }
        while (right >= left and S[right] != S[j]) {
            right -= 1;
        }

        if (left > right) {
            /*
            * consider the string from i to j is "a...a"
            * where there is no character 'a' inside the leftmost and rightmost 'a'
            *
            * eg:  "aba" while i = 0 and j = 2:  dp[1][1] = 1 records the palindrome{"b"},
            * the reason why dp[i + 1][j - 1] * 2 counted is that we count dp[i + 1][j - 1] one time as {"b"},
            * and additional time as {"aba"}. The reason why 2 counted is that we also count {"a", "aa"}.
            * So totally dp[i][j] record the palindrome: {"a", "b", "aa", "aba"}.
           */
            dp[i][j] = dp[i + 1][j - 1] * 2 + 2;
        }
        else if (left == right) {
            /*
            * consider the string from i to j is "a...a...a"
            * where there is only one character 'a' inside the leftmost and rightmost 'a'
            *
            * eg: "aaa" while i = 0 and j = 2: the dp[i + 1][j - 1] records the palindrome {"a"}.
            * the reason why dp[i + 1][j - 1] * 2 counted is that we count dp[i + 1][j - 1] one time as {"a"},
            * and additional time as {"aaa"}. the reason why 1 counted is that
            * we also count {"aa"} that the first 'a' come from index i and the second come from index j.
            * So totally dp[i][j] records {"a", "aa", "aaa"}
           */
            dp[i][j] = dp[i + 1][j - 1] * 2 + 1;
        }
        else {
            /*
            * consider the string from i to j is "a...a...a... a"
            * where there are at least two character 'a' close to leftmost and rightmost 'a'
            *
            * eg: "aacaa" while i = 0 and j = 4: the dp[i + 1][j - 1] records the palindrome {"a",  "c", "aa", "aca"}.
            * the reason why dp[i + 1][j  - 1] * 2 counted is that we count dp[i + 1][j - 1] one time as {"a",  "c", "aa", "aca"},
            * and additional time as {"aaa",  "aca", "aaaa", "aacaa"}.
            * Now there is duplicate :  {"aca"},
            * which is removed by deduce dp[low + 1][high - 1].
            * So totally dp[i][j] record {"a",  "c", "aa", "aca", "aaa", "aaaa", "aacaa"}
           */
            dp[i][j] = dp[i + 1][j - 1] * 2 - dp[left + 1][right - 1];
        }
    }
public:
    int countPalindromicSubsequences(string S) {
        int n = S.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }

        for (int len = 1; len < n; len++) {
            for (int i = 0; i + len < n; i++) {
                int j = i + len;
                update(i, j, dp, S);
                if (dp[i][j] < 0) {
                    dp[i][j] += MOD;
                }
                dp[i][j] %= MOD;
            }
        }
        return dp[0][n - 1];
    }
};
