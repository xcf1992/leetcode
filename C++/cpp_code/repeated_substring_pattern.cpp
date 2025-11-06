/*
459. Repeated Substring Pattern
https://leetcode.com/problems/repeated-substring-pattern/

Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the
substring together. You may assume the given string consists of lowercase English letters only and its length will not
exceed 10000.

Example 1:
Input: "abab"
Output: True
Explanation: It's the substring "ab" twice.

Example 2:
Input: "aba"
Output: False

Example 3:
Input: "abcabcabcabc"
Output: True
Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)
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
using namespace std;

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int length = s.size();
        for (int i = 1; i <= s.size() / 2; i++) {
            if (s[i] != s[0] or length % i != 0) {
                continue;
            }

            string pattern = s.substr(0, i);
            bool match = true;
            for (int j = 1; j < length / i; j++) {
                string sub = s.substr(j * i, i);
                if (sub != pattern) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
        return false;
    }
};