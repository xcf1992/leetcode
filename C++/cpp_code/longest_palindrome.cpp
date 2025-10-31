/*
409. Longest Palindrome

Given a string which consists of lowercase or uppercase letters,
find the length of the longest palindromes that can be built with those letters.

This is case-sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:
Input:
"abccccdd"
Output:
7
Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
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
using namespace std;

class Solution {
public:
    int longestPalindrome(string s) {
        vector<int> count(256, 0);
        for (char c : s) {
            count[c] += 1;
        }

        int result = 0;
        int odds = 0;
        for (int num : count) {
            odds += num & 1;
        }
        return s.size() - odds + (odds > 0 ? 1 : 0);
    }
};
