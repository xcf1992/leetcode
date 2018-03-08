/*
 Given a pattern and a string str, find if str follows the same pattern.
 
 Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.
 
 Examples:
 pattern = "abab", str = "redblueredblue" should return true.
 pattern = "aaaa", str = "asdasdasdasd" should return true.
 pattern = "aabb", str = "xyzabcxzyabc" should return false.
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
        if (i == m || j == n) {
            if (i == m && j == n) {
                return true;
            }
            return false;
        }
        
        bool result = false;
        for (int k = j; k < n; k++) {
            string word = str.substr(j, k - j + 1);
            if (pat2Str.find(pattern[i]) != pat2Str.end()) {
                if (pat2Str[pattern[i]] != word) {
                    continue;
                }
            }
            else if (str2Pat.find(word) != str2Pat.end()) {
                if (str2Pat[word] != pattern[i]) {
                    continue;
                }
            }
            else {
                pat2Str[pattern[i]] = word;
                str2Pat[word] = pattern[i];
                result = true;
            }
            if (match(pattern, i + 1, str, k + 1)) {
                return true;
            }
            if (result) {
                pat2Str.erase(pattern[i]);
                str2Pat.erase(word);
                result = false;
            }
        }
        return false;
    }
public:
    bool wordPatternMatch(string pattern, string str) {
        return match(pattern, 0, str, 0);
    }
};
