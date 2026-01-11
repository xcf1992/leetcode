/*
https://leetcode.com/problems/word-pattern
290. Word Pattern

Given a pattern and a string str, find if str follows the same pattern.
Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Example 1:
Input: pattern = "abba", str = "dog cat cat dog"
Output: true

Example 2:
Input:pattern = "abba", str = "dog cat cat fish"
Output: false

Example 3:
Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false

Example 4:
Input: pattern = "abba", str = "dog dog dog dog"
Output: false

Notes:
You may assume pattern contains only lowercase letters,
and str contains lowercase letters that may be separated by a single space.
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
    vector<string> get_words(string str) {
        vector<string> words;
        for (int pos = 0; (pos = str.find(' ')) != string::npos; str = str.substr(pos + 1)) {
            words.push_back(str.substr(0, pos));
        }
        if (str != "") {
            words.push_back(str);
        }
        return words;
    }

public:
    bool wordPattern(string pattern, string str) {
        vector<string> words = get_words(str);
        if (pattern.size() != words.size()) {
            return false;
        }

        unordered_map<char, string> pat_to_str;
        unordered_map<string, char> str_to_pat;
        for (int i = 0; i < pattern.size(); i++) {
            if (pat_to_str.find(pattern[i]) == pat_to_str.end()) {
                if (str_to_pat.find(words[i]) != str_to_pat.end()) {
                    return false;
                }

                pat_to_str[pattern[i]] = words[i];
                str_to_pat[words[i]] = pattern[i];
                continue;
            }

            if (pat_to_str[pattern[i]] != words[i]) {
                return false;
            }
        }
        return true;
    }
};