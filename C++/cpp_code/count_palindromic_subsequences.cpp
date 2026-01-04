/*
https://leetcode.com/problems/count-palindromic-subsequences/description/
2484. Count Palindromic Subsequences

Given a string of digits s, return the number of palindromic subsequences of s having length 5. Since the answer may be
very large, return it modulo 109 + 7.

Note:

A string is palindromic if it reads the same forward and backward.
A subsequence is a string that can be derived from another string by deleting some or no characters without changing the
order of the remaining characters.


Example 1:

Input: s = "103301"
Output: 2
Explanation:
There are 6 possible subsequences of length 5: "10330","10331","10301","10301","13301","03301".
Two of them (both equal to "10301") are palindromic.
Example 2:

Input: s = "0000000"
Output: 21
Explanation: All 21 subsequences are "00000", which is palindromic.
Example 3:

Input: s = "9999900000"
Output: 2
Explanation: The only two palindromic subsequences are "99999" and "00000".


Constraints:

1 <= s.length <= 104
s consists of digits.
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
using namespace std;
/*
Intuition
To create a 5 digit palindrome we do not need to care about the middle element. We just need to find subsequence of
pattern XY_YX. Calculate number of subsequences of type XY and subsequences of type YX around any given point i and
multiply them to find number of subsequences of type XY_YX. Since string only has digits, the time complexity will be
100*n.

Approach
We will be maintaing the counts of digit in the list cnts
Keep 2 arrays pre and suf to store the number of prefixes of type XY and suffixes of type YX. pre[i-1][1][2] means
prefixes of type 12 before index i. Similarly suf[i+1][1][2] means suffixes of type 21 after index i Remember given
string is made of digits that is 0123456789. That's a total of 10 unique characters Once we have calculated the prefix
and suffix lists we just need to multiply pre[i - 1][j][k] with suf[i + 1][j][k] to find number of palindromic
subsequences
 */
class Solution {
public:
    int pre[10000][10][10], suf[10000][10][10], cnts[10] = {};
    int countPalindromes(string s) {
        int mod = 1e9 + 7, n = s.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - '0';
            if (i)
                for (int j = 0; j < 10; j++)
                    for (int k = 0; k < 10; k++) {
                        pre[i][j][k] = pre[i - 1][j][k];
                        if (k == c)
                            pre[i][j][k] += cnts[j];
                    }
            cnts[c]++;
        }
        memset(cnts, 0, sizeof(cnts));
        for (int i = n - 1; i >= 0; i--) {
            int c = s[i] - '0';
            if (i < n - 1)
                for (int j = 0; j < 10; j++)
                    for (int k = 0; k < 10; k++) {
                        suf[i][j][k] = suf[i + 1][j][k];
                        if (k == c)
                            suf[i][j][k] += cnts[j];
                    }
            cnts[c]++;
        }
        for (int i = 2; i < n - 2; i++)
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 10; k++)
                    ans = (ans + 1LL * pre[i - 1][j][k] * suf[i + 1][j][k]) % mod;
        return ans;
    }
};