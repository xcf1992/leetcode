/*
1397. Find All Good Strings
https://leetcode.com/problems/find-all-good-strings/

Given the strings s1 and s2 of size n, and the string evil.
Return the number of good strings.

A good string has size n, it is alphabetically greater than or equal to s1,
it is alphabetically smaller than or equal to s2,
and it does not contain the string evil as a substring.
Since the answer can be a huge number, return this modulo 10^9 + 7.

Example 1:
Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
Output: 51
Explanation: There are 25 good strings starting with 'a': "aa","ac","ad",...,"az". Then there are 25 good strings
starting with 'c': "ca","cc","cd",...,"cz" and finally there is one good string starting with 'd': "da".

Example 2:
Input: n = 8, s1 = "leetcode", s2 = "leetgoes", evil = "leet"
Output: 0
Explanation: All strings greater than or equal to s1 and smaller than or equal to s2 start with the prefix "leet",
therefore, there is not any good string.

Example 3:
Input: n = 2, s1 = "gx", s2 = "gz", evil = "x"
Output: 2

Constraints:
s1.length == n
s2.length == n
s1 <= s2
1 <= n <= 500
1 <= evil.length <= 50
All strings consist of lowercase English letters.
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
#include <set>
#include <numeric>
using namespace std;

// https://leetcode.com/problems/find-all-good-strings/discuss/555591/JavaC%2B%2B-Memoization-DFS-and-KMP-with-Picture-Clean-code-~-12ms
class Solution {
public:
    int dp[501][51][2][2] = {};

    int findGoodStrings(int n, string s1, string s2, string evil) {
        return dfs(0, 0, true, true, n, s1, s2, evil, computeLPS(evil));
    }

    int dfs(int i, int evilMatched, bool leftBound, bool rightBound, int n, string& s1, string& s2, string& evil,
            const vector<int>& lps) {
        if (evilMatched == evil.size())
            return 0;  // contain `evil` as a substring -> not good string
        if (i == n)
            return 1;  // it's a good string
        if (dp[i][evilMatched][leftBound][rightBound] != 0)
            return dp[i][evilMatched][leftBound][rightBound];
        char from = leftBound ? s1[i] : 'a';
        char to = rightBound ? s2[i] : 'z';
        int res = 0;
        for (char c = from; c <= to; c++) {
            int j = evilMatched;  // j means the next match between current string (end at char `c`) and `evil` string
            while (j > 0 && evil[j] != c)
                j = lps[j - 1];
            if (c == evil[j])
                j++;
            res += dfs(i + 1, j, leftBound && (c == from), rightBound && (c == to), n, s1, s2, evil, lps);
            res %= 1000000007;
        }
        return dp[i][evilMatched][leftBound][rightBound] = res;
    }

    vector<int> computeLPS(const string& str) {
        // Longest Prefix also Suffix
        int n = str.size();
        vector<int> lps = vector<int>(n);
        for (int i = 1, j = 0; i < n; i++) {
            while (j > 0 && str[i] != str[j])
                j = lps[j - 1];
            if (str[i] == str[j])
                lps[i] = ++j;
        }
        return lps;
    }
};