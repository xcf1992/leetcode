/*
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"
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

// brute force O(n ^ 2)
class Solution {
public:
    string expand(string s, int c1, int c2) {
        while (c1 >= 0 && c2 < s.size() && s[c1] == s[c2]) {
            c1--;
            c2++;
        }
        return s.substr(c1 + 1, c2 - c1 - 1);
    }
    
    string longestPalindrome(string s) {
        if (s.size() <= 1) {
            return s;
        }
        
        string result = s.substr(0, 1);
        for (int i = 0; i < s.size(); i++) {
            string p1 = expand(s, i, i);
            if (result.size() < p1.size()) {
                result = p1;
            }
            
            string p2 = expand(s, i, i + 1);
            if (result.size() < p2.size()) {
                result = p2;
            }
        }
        
        return result;
    }
};