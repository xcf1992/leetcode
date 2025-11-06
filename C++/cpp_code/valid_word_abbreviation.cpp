/*
 Given a non-empty string s and an abbreviation abbr, return whether the string matches with the given abbreviation.

 A string such as "word" contains only the following valid abbreviations:

 ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
 Notice that only the above abbreviations are valid abbreviations of the string "word". Any other string is not a valid
 abbreviation of "word".

 Note:
 Assume s contains only lowercase letters and abbr contains only lowercase letters and digits.

 Example 1:
 Given s = "internationalization", abbr = "i12iz4n":

 Return true.
 Example 2:
 Given s = "apple", abbr = "a2e":

 Return false.
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
public:
    bool validWordAbbreviation(string word, string abbr) {
        int pos = 0;
        int cur = 0;
        while (cur < word.size() and pos < abbr.size()) {
            if (abbr[pos] == '0') {
                return false;
            }
            if (isdigit(abbr[pos])) {
                int start = pos;
                while (pos < abbr.size() and isdigit(abbr[pos])) {
                    pos += 1;
                }
                cur += stoi(abbr.substr(start, pos - start));
            } else {
                if (word[cur] != abbr[pos]) {
                    return false;
                }
                cur += 1;
                pos += 1;
            }
        }
        return cur == word.size() and pos == abbr.size();
    }
};