/*
1278. Palindrome Partitioning III
https://leetcode.com/problems/palindrome-partitioning-iii/

You are given a string s containing lowercase letters and an integer k.
You need to :
First, change some characters of s to other lowercase English letters.
Then divide s into k non-empty disjoint substrings such that each substring is palindrome.
Return the minimal number of characters that you need to change to divide the string.

Example 1:
Input: s = "abc", k = 2
Output: 1
Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.

Example 2:
Input: s = "aabbc", k = 3
Output: 0
Explanation: You can split the string into "aa", "bb" and "c", all of them are palindrome.

Example 3:
Input: s = "leetcode", k = 8
Output: 0

Constraints:
1 <= k <= s.length <= 100.
s only contains lowercase English letters.
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
We create 2 dp arrays
pd[i][j] = stores the minimum changes required to convert a string starting from i to j into palindrome (i.e for k=1)
dp[j][k] = min changes to divide the string into k palindromic substrings starting from 0th index to jth index.

Constructing pd:
1. pd[i][i] : always 0, since a single character is always palindrome.
2. pd[i][i+1] : 0 or 1 depending on whether both characters are same or not.
3. pd[i][j] :
   a. if s[i] == s[j] : pd[i][j] = pd[i+1][j-1]
   b. else pd[i][j] = pd[i+1][j-1] + 1, because we can change character at either ith position or jth position.

Constructing dp:
1. dp[i][1] = pd[0][i] ; because pd is constructed for k = 1.
2. Now the main recurrence intution:
   dp[i][k] = min(dp[l][k-1] + pd[l+1][i]); where l varies from 0 to i.
*/
class Solution {
public:
    int palindromePartition(string s, int K) {
        int len = s.size();
        vector<vector<int>> minChange(len + 1, vector<int>(len + 1, len + 1));
        vector<vector<int>> minDivide(len + 1, vector<int>(len + 1, len + 1));

        for (int i = 0; i < len; ++i) {
            minChange[i][i] = 0;
            if (i < len - 1) {
                minChange[i][i + 1] = s[i] == s[i + 1] ? 0 : 1;
            }
        }
        for (int k = 2; k < len; ++k) {
            for (int i = 0; i + k < len; ++i) {
                int j = i + k;
                minChange[i][j] = minChange[i + 1][j - 1] + (s[i] == s[j] ? 0 : 1);
            }
        }

        for (int i = 0; i < len; ++i) {
            minDivide[i][1] = minChange[0][i];
        }
        for (int k = 2; k <= K; ++k) {
            for (int i = 1; i < len; ++i) {
                minDivide[i][k] = i + 1;
                for (int j = 0; j <= i; ++j) {
                    minDivide[i][k] = min(minDivide[i][k], minDivide[j][k - 1] + minChange[j + 1][i]);
                }
            }
        }
        return minDivide[len - 1][K];
    }
};
