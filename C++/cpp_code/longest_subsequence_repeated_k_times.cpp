/*
https://leetcode.com/problems/longest-subsequence-repeated-k-times/description/
2014. Longest Subsequence Repeated k Times

You are given a string s of length n, and an integer k. You are tasked to find the longest subsequence repeated k times
in string s.

A subsequence is a string that can be derived from another string by deleting some or no characters without changing the
order of the remaining characters.

A subsequence seq is repeated k times in the string s if seq * k is a subsequence of s, where seq * k represents a
string constructed by concatenating seq k times.

For example, "bba" is repeated 2 times in the string "bababcba", because the string "bbabba", constructed by
concatenating "bba" 2 times, is a subsequence of the string "bababcba". Return the longest subsequence repeated k times
in string s. If multiple such subsequences are found, return the lexicographically largest one. If there is no such
subsequence, return an empty string.

Example 1:

example 1
Input: s = "letsleetcode", k = 2
Output: "let"
Explanation: There are two longest subsequences repeated 2 times: "let" and "ete".
"let" is the lexicographically largest one.
Example 2:

Input: s = "bb", k = 2
Output: "b"
Explanation: The longest subsequence repeated 2 times is "b".
Example 3:

Input: s = "ab", k = 2
Output: ""
Explanation: There is no subsequence repeated 2 times. Empty string is returned.


Constraints:

n == s.length
2 <= k <= 2000
2 <= n < min(2001, k * 8)
s consists of lowercase English letters.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class Solution {
private:
    bool repeated_k_times(string& sub, string& origin_str, int k) {
        int cnt = 0;
        int idx = 0;
        int n = sub.size();
        for (char& ch : origin_str) {
            if (ch != sub[idx]) {
                continue;
            }

            idx += 1;
            if (idx == n) {
                cnt += 1;
                idx = 0;
            }

            if (cnt == k) {
                return true;
            }
        }
        return false;
    }
public:
    string longestSubsequenceRepeatedK(string s, int k) {
        vector<int> freq(26, 0);
        unordered_set<char> candidate;
        for (char& ch : s) {
            freq[ch - 'a'] += 1;
            if (freq[ch - 'a'] >= k && candidate.find(ch) == candidate.end()) {
                candidate.insert(ch);
            }
        }

        queue<string> bfs;
        bfs.push("");
        string rst = "";
        int len_cap = s.size() / k;
        while (!bfs.empty()) {
            string cur = bfs.front();
            bfs.pop();

            for (char ch : candidate) {
                string nxt = cur + ch;
                if (nxt.size() > len_cap) {
                    break;
                }

                if (!repeated_k_times(nxt, s, k)) {
                    continue;
                }

                bfs.push(nxt);
                if (nxt.size() > rst.size() || nxt > rst) {
                    rst = nxt;
                }
            }
        }
        return rst;
    }
};
