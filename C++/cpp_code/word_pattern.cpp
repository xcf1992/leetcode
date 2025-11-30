/*
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
    vector<string> getWords(string str) {
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
        vector<string> words = getWords(str);
        if (pattern.length() != words.size()) {
            return false;
        }

        unordered_map<char, string> pat2Str;
        unordered_map<string, char> str2Pat;
        for (int i = 0; i < pattern.size(); i++) {
            if (pat2Str.find(pattern[i]) == pat2Str.end()) {
                if (str2Pat.find(words[i]) != str2Pat.end()) {
                    return false;
                }
                pat2Str[pattern[i]] = words[i];
                str2Pat[words[i]] = pattern[i];
            }
            if (pat2Str[pattern[i]] != words[i]) {
                return false;
            }
        }
        return true;
    }
};