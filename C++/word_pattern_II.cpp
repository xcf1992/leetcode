/*
291. Word Pattern II
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

Example 1:

Input: pattern = "abab", str = "redblueredblue"
Output: true
Example 2:

Input: pattern = pattern = "aaaa", str = "asdasdasdasd"
Output: true
Example 3:

Input: pattern = "aabb", str = "xyzabcxzyabc"
Output: false
Notes:
You may assume both pattern and str contains only lowercase letters.
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
private:
    unordered_map<char, string> pat2Str;
    unordered_map<string, char> str2Pat;

    bool match(string &pattern, int i, string &str, int j) {
        int m = pattern.size();
        int n = str.size();
        if (i == m and j == n) {
            return true;
        }
        if (i == m or j == n) {
            return false;
        }

        if (pat2Str.find(pattern[i]) != pat2Str.end()) {
            string word = pat2Str[pattern[i]];
            if (word == str.substr(j, word.size())) {
                return match(pattern, i + 1, str, j + word.size());
            }
            return false;
        }

        for (int k = j; k < n; k++) {
            string word = str.substr(j, k - j + 1);
            if (str2Pat.find(word) != str2Pat.end()) {
                continue;
            }

            pat2Str[pattern[i]] = word;
            str2Pat[word] = pattern[i];
            if (match(pattern, i + 1, str, k + 1)) {
                return true;
            }
            pat2Str.erase(pattern[i]);
            str2Pat.erase(word);
        }
        return false;
    }
public:
    bool wordPatternMatch(string pattern, string str) {
        return match(pattern, 0, str, 0);
    }
};
