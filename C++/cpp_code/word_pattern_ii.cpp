/*
https://leetcode.com/problems/word-pattern-ii/
291. Word Pattern II

Given a pattern and a string str,
find if str follows the same pattern.
Here follow means a full match,
such that there is a bijection between a letter in pattern and a non-empty substring in str.

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
#include <climits>
using namespace std;

class Solution {
private:
    unordered_map<char, string> pat_to_str_;
    unordered_map<string, char> str_to_pat_;

    bool match(string& pattern, int i, string& str, int j) {
        int m = pattern.size();
        int n = str.size();
        if (i == m && j == n) {
            return true;
        }

        if (i == m or j == n) {
            return false;
        }

        if (pat_to_str_.find(pattern[i]) != pat_to_str_.end()) {
            string word = pat_to_str_[pattern[i]];
            if (word == str.substr(j, word.size())) {
                return match(pattern, i + 1, str, j + word.size());
            }
            return false;
        }

        for (int len = 1; j + len - 1 < n; len++) {
            string word = str.substr(j, len);
            if (str_to_pat_.find(word) != str_to_pat_.end()) {
                continue;
            }

            pat_to_str_[pattern[i]] = word;
            str_to_pat_[word] = pattern[i];
            if (match(pattern, i + 1, str, j + len)) {
                return true;
            }
            pat_to_str_.erase(pattern[i]);
            str_to_pat_.erase(word);
        }
        return false;
    }

public:
    bool wordPatternMatch(string pattern, string str) {
        return match(pattern, 0, str, 0);
    }
};