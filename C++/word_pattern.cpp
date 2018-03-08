/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:
pattern = "abba", str = "dog cat cat dog" should return true.
pattern = "abba", str = "dog cat cat fish" should return false.
pattern = "aaaa", str = "dog cat cat dog" should return false.
pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.
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
    bool wordPattern(string pattern, string str) {
        vector<string> words;
        string temp;
        for (char c : str) {
            if (c != ' ') {
                temp += c;
            }
            else {
                words.push_back(temp);
                temp = "";
            }
        }
        words.push_back(temp);
        
        if (pattern.length()!= words.size()) {
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