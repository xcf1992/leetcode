/*
392. Is Subsequence
Given a string s and a string t, check if s is subsequence of t.

You may assume that there is only lower case English letters in both s and t.
t is potentially a very long (length ~= 500,000) string,
and s is a short string (<=100).

A subsequence of a string is a new string
which is formed from the original string by deleting some (can be none) of the characters
without disturbing the relative positions of the remaining characters.
(ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B,
and you want to check one by one to see if T has its subsequence.
In this scenario, how would you change your code?
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
public:
    bool isSubsequence(string t, string s) {
        vector<vector<int>> pos(26);
        for (int i = 0; i < s.size(); ++i) {
            pos[s[i] - 'a'].push_back(i);
        }

        int cur = -1;
        for (int j = 0; j < t.size(); ++j) {
            auto it = upper_bound(pos[t[j] - 'a'].begin(), pos[t[j] - 'a'].end(), cur);
            if (it == pos[t[j] - 'a'].end()) {
                return false;
            }
            cur = *it;
        }
        return true;
    }
};

class Solution1 {
public:
    bool isSubsequence(string s, string t) {
        int sPtr = 0;
        int tPtr = 0;
        while (sPtr < s.size() and tPtr < t.size()) {
            if (s[sPtr] == t[tPtr]) {
                sPtr++;
            }
            tPtr++;
        }
        return sPtr == s.size();
    }
};