/*
467. Unique Substrings in Wraparound String
Consider the string s to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz",
so s will look like this: "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".

Now we have another string p.
Your job is to find out how many unique non-empty substrings of p are present in s.
In particular,
your input is the string p and you need to output the number of different non-empty substrings of p in the string s.

Note: p consists of only lowercase English letters and the size of p might be over 10000.

Example 1:
Input: "a"
Output: 1
Explanation: Only the substring "a" of string "a" is in the string s.

Example 2:
Input: "cac"
Output: 2
Explanation: There are two substrings "a", "c" of string "cac" in the string s.

Example 3:
Input: "zab"
Output: 6
Explanation: There are six substrings "z", "a", "b", "za", "ab", "zab" of string "zab" in the string s.
*/
#include <iostream>
#include <sstream>
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
    int findSubstringInWraproundString(string p) {
        int n = p.size();
        if (n < 2) {
            return n;
        }

        vector<int> counts(26, 0);
        int start = 0;
        int end = 1;
        while (end <= n) {
            while (end < n and (p[end - 1] - 'a' + 1) % 26 == (p[end] - 'a')) {
                end += 1;
            }
            while (start < end) {
                counts[p[start] - 'a'] = max(end - start, counts[p[start] - 'a']);
                start += 1;
            }
            end += 1;
        }

        int result = 0;
        for (int count : counts) {
            result += count;
        }
        return result;
    }
};