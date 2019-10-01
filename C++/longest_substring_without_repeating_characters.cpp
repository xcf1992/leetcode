/*
3. Longest Substring Without Repeating Characters
https://leetcode.com/problems/longest-substring-without-repeating-characters/

Given a string, find the length of the longest substring without repeating characters.

Example 1:
Input: "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() <= 1) {
            return s.size();
        }

        int begin = 0;
        int end = 1;
        int result = 1;
        unordered_map<char, int> pos;
        pos[s[begin]] = 0;
        while (end < s.size()) {
            if (pos.find(s[end]) != pos.end() and pos[s[end]] >= begin) {
                result = max(result, end - begin);
                begin = pos[s[end]] + 1;
            }
            pos[s[end]] = end;
            end++;
        }
        return max(result, end - begin);
    }
};
