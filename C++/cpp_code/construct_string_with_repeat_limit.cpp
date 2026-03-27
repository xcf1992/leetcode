/*
https://leetcode.com/problems/construct-string-with-repeat-limit/description/
2182. Construct String With Repeat Limit
You are given a string s and an integer repeatLimit. Construct a new string repeatLimitedString using the characters of
s such that no letter appears more than repeatLimit times in a row. You do not have to use all characters from s.

Return the lexicographically largest repeatLimitedString possible.

A string a is lexicographically larger than a string b if in the first position where a and b differ, string a has a
letter that appears later in the alphabet than the corresponding letter in b. If the first min(a.length, b.length)
characters do not differ, then the longer string is the lexicographically larger one.



Example 1:

Input: s = "cczazcc", repeatLimit = 3
Output: "zzcccac"
Explanation: We use all of the characters from s to construct the repeatLimitedString "zzcccac".
The letter 'a' appears at most 1 time in a row.
The letter 'c' appears at most 3 times in a row.
The letter 'z' appears at most 2 times in a row.
Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
The string is the lexicographically largest repeatLimitedString possible so we return "zzcccac".
Note that the string "zzcccca" is lexicographically larger but the letter 'c' appears more than 3 times in a row, so it
is not a valid repeatLimitedString. Example 2:

Input: s = "aababab", repeatLimit = 2
Output: "bbabaa"
Explanation: We use only some of the characters from s to construct the repeatLimitedString "bbabaa".
The letter 'a' appears at most 2 times in a row.
The letter 'b' appears at most 2 times in a row.
Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
The string is the lexicographically largest repeatLimitedString possible so we return "bbabaa".
Note that the string "bbabaaa" is lexicographically larger but the letter 'a' appears more than 2 times in a row, so it
is not a valid repeatLimitedString.


Constraints:

1 <= repeatLimit <= s.length <= 105
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a'] += 1;
        }

        priority_queue<pair<char, int>, vector<pair<char, int>>, less<pair<char, int>>> pq;
        for (int i = 0; i < 26; i++) {
            if (freq[i] != 0) {
                pq.push({'a' + i, freq[i]});
            }
        }

        string rst = "";
        while (!pq.empty()) {
            char c = pq.top().first;
            int cnt = pq.top().second;
            pq.pop();

            int used = min(repeatLimit, cnt);
            rst += string(used, c);
            cnt -= used;
            if (cnt > 0 && !pq.empty()) {
                char next_char = pq.top().first;
                int next_cnt = pq.top().second;
                pq.pop();

                rst.push_back(next_char);
                next_cnt -= 1;
                if (next_cnt > 0) {
                    pq.push({next_char, next_cnt});
                }
                pq.push({c, cnt});
            }
        }
        return rst;
    }
};
