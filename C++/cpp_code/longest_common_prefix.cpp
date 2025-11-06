/*
14. Longest Common Prefix
https://leetcode.com/problems/longest-common-prefix/

Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".

Example 1:
Input: ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.

Note:
All given inputs are in lowercase letters a-z.
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
    bool isCommon(vector<string>& strs, int len) {
        string prefix = strs[0].substr(0, len);
        for (int i = 1; i < strs.size(); ++i) {
            string cur = strs[i].substr(0, len);
            if (prefix != cur) {
                return false;
            }
        }
        return true;
    }

public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        if (n == 0) {
            return "";
        }
        if (n == 1) {
            return strs[0];
        }

        int minLen = INT_MAX;
        for (string& s : strs) {
            minLen = min(minLen, (int)s.size());
        }

        int left = 0;
        int right = minLen;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (!isCommon(strs, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return strs[0].substr(0, (left + right) / 2);
    }
};

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty())
            return "";
        sort(strs.begin(), strs.end());
        string a = strs[0], b = strs.back();
        int i = 0;
        for (; i < min(a.size(), b.size()); i++)
            if (a[i] != b[i])
                break;
        return a.substr(0, i);
    }
};

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }

        int prefix = -1;
        string cur = strs[0];
        for (int i = 1; i <= cur.size(); ++i) {
            bool allMatch = true;
            for (int j = 1; j < strs.size(); ++j) {
                string next = strs[j];
                if (i > next.size() or cur[i - 1] != next[i - 1]) {
                    allMatch = false;
                    break;
                }
            }

            if (!allMatch) {
                break;
            }
            prefix = i;
        }
        return prefix == -1 ? "" : cur.substr(0, prefix);
    }
};