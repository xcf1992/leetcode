/*
https://leetcode.com/problems/longest-balanced-substring-i/description/
3713. Longest Balanced Substring I

You are given a string s consisting of lowercase English letters.

A substring of s is called balanced if all distinct characters in the substring appear the same number of times.

Return the length of the longest balanced substring of s.



Example 1:

Input: s = "abbac"

Output: 4

Explanation:

The longest balanced substring is "abba" because both distinct characters 'a' and 'b' each appear exactly 2 times.

Example 2:

Input: s = "zzabccy"

Output: 4

Explanation:

The longest balanced substring is "zabc" because the distinct characters 'z', 'a', 'b', and 'c' each appear exactly 1
time.​​​​​​​

Example 3:

Input: s = "aba"

Output: 2

Explanation:

​​​​​​​One of the longest balanced substrings is "ab" because both distinct characters 'a' and 'b' each
appear exactly 1 time. Another longest balanced substring is "ba".



Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.
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
    bool is_balanced(vector<int>& freq) {
        int cur_max = INT_MIN;
        int cur_min = INT_MAX;
        for (int cnt : freq) {
            if (cnt == 0) {
                continue;
            }

            cur_max = max(cur_max, cnt);
            cur_min = min(cur_min, cnt);
        }
        return cur_max == cur_min;
    }
public:
    int longestBalanced(string s) {
        int n = s.size();
        for (int len = n; len > 2; len--) {
            vector<int> freq(26, 0);
            for (int i = 0; i < len; i++) {
                freq[s[i] - 'a'] += 1;
            }

            if (is_balanced(freq)) {
                return len;
            }

            for (int i = len; i < n; i++) {
                freq[s[i] - 'a'] += 1;
                freq[s[i - len] - 'a'] -= 1;
                if (is_balanced(freq)) {
                    return len;
                }
            }
        }
        return min(2, n);
    }
};