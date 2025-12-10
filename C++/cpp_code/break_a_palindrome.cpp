/*
1328. Break a Palindrome
https://leetcode.com/problems/break-a-palindrome/

Given a palindromic string palindrome,
replace exactly one character by any lowercase English letter
so that the string becomes the lexicographically smallest possible string that isn't a palindrome.

After doing so, return the final string.
If there is no way to do so, return the empty string.

Example 1:
Input: palindrome = "abccba"
Output: "aaccba"

Example 2:
Input: palindrome = "a"
Output: ""

Constraints:
1 <= palindrome.length <= 1000
palindrome consists of only lowercase English letters.
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

class Solution {
public:
    string breakPalindrome(string S) {
        int n = S.size();
        for (int i = 0; i < n / 2; ++i) {
            if (S[i] != 'a') {
                S[i] = 'a';
                return S;
            }
        }
        S[n - 1] = 'b';
        return n < 2 ? "" : S;
    }
};