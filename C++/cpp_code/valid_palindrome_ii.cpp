/*
https://leetcode.com/problems/valid-palindrome-ii/
680. Valid Palindrome II

Given a non-empty string s, you may delete at most one character.
Judge whether you can make it a palindrome.

Example 1:
Input: "aba"
Output: True

Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.

Note:
The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
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
#include <set>
using namespace std;

class Solution {
private:
    bool check(string& s, bool& skip, int left, int right) {
        if (left >= right) {
            return true;
        }

        if (s[left] == s[right]) {
            return check(s, skip, left + 1, right - 1);
        }

        if (skip) {
            return false;
        }

        skip = true;
        return check(s, skip, left + 1, right) || check(s, skip, left, right - 1);
    }

public:
    bool validPalindrome(string s) {
        bool skip = false;
        int left = 0;
        int right = s.size() - 1;
        return check(s, skip, left, right);
    }
};