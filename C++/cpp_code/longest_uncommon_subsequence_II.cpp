/*
522. Longest Uncommon Subsequence II

Given a list of strings, you need to find the longest uncommon subsequence among them.
The longest uncommon subsequence is defined as the longest subsequence of one of these strings and
this subsequence should not be any subsequence of the other strings.

A subsequence is a sequence that can be derived from one sequence
by deleting some characters without changing the order of the remaining elements.
Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.

The input will be a list of strings, and the output needs to be the length of the longest uncommon subsequence.
If the longest uncommon subsequence doesn't exist, return -1.

Example 1:
Input: "aba", "cdc", "eae"
Output: 3
Note:

All the given strings' lengths will not exceed 10.
The length of the given list will be in the range of [2, 50].
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
    bool isSub(const string a, const string b) {
        int i = 0;
        int j = 0;
        while (i < a.size() and j < b.size()) {
            if (a[i] == b[j]) {
                i++;
            }
            j++;
        }
        return i == a.size();
    }

public:
    int findLUSlength(vector<string>& strs) {
        sort(strs.begin(), strs.end(), [](const string a, const string b) { return a.size() > b.size(); });

        unordered_map<string, int> count;
        for (string str : strs) {
            count[str] += 1;
        }

        for (int i = 0; i < strs.size(); i++) {
            if (count[strs[i]] != 1) {
                continue;
            }

            int j = 0;
            while (j < i) {
                if (isSub(strs[i], strs[j])) {
                    break;
                }
                j++;
            }
            if (j == i) {
                return strs[i].size();
            }
        }
        return -1;
    }
};