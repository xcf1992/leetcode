/*
249. Group Shifted Strings
https://leetcode.com/problems/group-shifted-strings/

Given a string,
we can "shift" each of its letter to its successive letter,
for example: "abc" -> "bcd".
We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"
Given a list of strings which contains only lowercase alphabets,
group all strings that belong to the same shifting sequence.

Example:
Input: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Output:
[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> pattern;
        for (string& str : strings) {
            string curPat = "";
            for (int i = 1; i < str.size(); ++i) {
                int gap = (str[i] + 26 - str[i - 1]) % 26;
                curPat.push_back('0' + gap);
            }
            pattern[curPat].push_back(str);
        }

        vector<vector<string>> result;
        for (auto& it : pattern) {
            result.push_back(it.second);
        }
        return result;
    }
};