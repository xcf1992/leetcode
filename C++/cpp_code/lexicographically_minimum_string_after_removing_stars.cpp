/*
https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/description/
3170. Lexicographically Minimum String After Removing Stars

You are given a string s. It may contain any number of '*' characters. Your task is to remove all '*' characters.

While there is a '*', do the following operation:

Delete the leftmost '*' and the smallest non-'*' character to its left. If there are several smallest characters, you
can delete any of them. Return the lexicographically smallest resulting string after removing all '*' characters.



Example 1:

Input: s = "aaba*"

Output: "aab"

Explanation:

We should delete one of the 'a' characters with '*'. If we choose s[3], s becomes the lexicographically smallest.

Example 2:

Input: s = "abc"

Output: "abc"

Explanation:

There is no '*' in the string.



Constraints:

1 <= s.length <= 105
s consists only of lowercase English letters and '*'.
The input is generated such that it is possible to delete all '*' characters.
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
    string clearStars(string s) {
        const int n = s.size();
        vector<vector<int>> pos(26);
        for (int i = 0; i < n; ++i) {
            if (s[i] != '*') {
                pos[s[i] - 'a'].push_back(i);
                continue;
            }

            for (int k = 0; k < 26; ++k) {
                if (!pos[k].empty()) {
                    s[pos[k].back()] = '*';
                    pos[k].pop_back();
                    break;
                }
            }
        }

        string rst;
        rst.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (s[i] != '*') {
                rst.push_back(s[i]);
            }
        }
        return rst;
    }
};

class Solution1 {  // TLE
private:
    char current_smallest_char(vector<int>& freq) {
        for (int i = 0; i < freq.size(); i++) {
            if (freq[i] != 0) {
                return 'a' + i;
            }
        }
        return 'a';
    }

public:
    string clearStars(string s) {
        size_t n = s.size();
        vector<int> freq(26, 0);
        string rst = "";
        for (size_t i = 0; i < n; i++) {
            if (std::islower(s[i])) {
                freq[s[i] - 'a'] += 1;
                rst.push_back(s[i]);
                continue;
            }

            char c = current_smallest_char(freq);
            freq[c - 'a'] -= 1;
            string temp = "";
            while (!rst.empty() && rst.back() != c) {
                temp.push_back(rst.back());
                rst.pop_back();
            }
            if (!rst.empty()) {
                rst.pop_back();
            }
            reverse(temp.begin(), temp.end());
            rst += temp;
        }
        return rst;
    }
};