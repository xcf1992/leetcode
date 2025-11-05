/*
1220. Count Vowels Permutation
https://leetcode.com/problems/count-vowels-permutation/

Given an integer n, your task is to count how many strings of length n can be formed under the following rules:

Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
Each vowel 'a' may only be followed by an 'e'.
Each vowel 'e' may only be followed by an 'a' or an 'i'.
Each vowel 'i' may not be followed by another 'i'.
Each vowel 'o' may only be followed by an 'i' or a 'u'.
Each vowel 'u' may only be followed by an 'a'.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: n = 1
Output: 5
Explanation: All possible strings are: "a", "e", "i" , "o" and "u".

Example 2:
Input: n = 2
Output: 10
Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".

Example 3:
Input: n = 5
Output: 68

Constraints:
1 <= n <= 2 * 10^4
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int countVowelPermutation(int n) {
        int mod = 1e9 + 7;
        vector<vector<int> > moves({{1}, {0, 2}, {0, 1, 3, 4}, {2, 4}, {0}}); // a e i o u
        vector<int> dp(5, 1);
        for (int i = 1; i < n; ++i) {
            vector<int> temp(5, 0);
            for (int last = 0; last < 5; ++last) {
                for (int nxt: moves[last]) {
                    temp[nxt] = (temp[nxt] + dp[last]) % mod;
                }
            }
            swap(dp, temp);
        }

        int result = 0;
        for (int count: dp) {
            result = (result + count) % mod;
        }
        return result;
    }
};