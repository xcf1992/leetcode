/*
1324. Print Words Vertically
https://leetcode.com/problems/print-words-vertically/

Given a string s.
Return all the words vertically in the same order in which they appear in s.
Words are returned as a list of strings,
complete with spaces when is necessary.
(Trailing spaces are not allowed).
Each word would be put on only one column and that in one column there will be only one word.

Example 1:
Input: s = "HOW ARE YOU"
Output: ["HAY","ORO","WEU"]
Explanation: Each word is printed vertically.
 "HAY"
 "ORO"
 "WEU"

Example 2:
Input: s = "TO BE OR NOT TO BE"
Output: ["TBONTB","OEROOE","   T"]
Explanation: Trailing spaces is not allowed.
"TBONTB"
"OEROOE"
"   T"

Example 3:
Input: s = "CONTEST IS COMING"
Output: ["CIC","OSO","N M","T I","E N","S G","T"]

Constraints:
1 <= s.length <= 200
s contains only upper case English letters.
It's guaranteed that there is only one space between 2 words.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<string> printVertically(string s) {
        int maxLen = 0;
        vector<string> words;
        string word = "";
        for (int i = 0; i <= s.size(); ++i) {
            if (i == s.size() or s[i] == ' ') {
                words.push_back(word);
                maxLen = max(maxLen, (int)word.size());
                word = "";
            } else {
                word.push_back(s[i]);
            }
        }

        vector<string> result(maxLen, "");
        for (int i = 0; i < maxLen; ++i) {
            for (string& word : words) {
                if (i >= word.size()) {
                    result[i].push_back(' ');
                } else {
                    result[i].push_back(word[i]);
                }
            }
        }

        for (string& token : result) {
            while (token.back() == ' ') {
                token.pop_back();
            }
        }
        return result;
    }
};