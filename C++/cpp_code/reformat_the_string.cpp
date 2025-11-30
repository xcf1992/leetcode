/*
1417. Reformat The String
https://leetcode.com/problems/reformat-the-string/

Given alphanumeric string s.
(Alphanumeric string is a string consisting of lowercase English letters and digits).

You have to find a permutation of the string
where no letter is followed by another letter and no digit is followed by another digit.
That is, no two adjacent characters have the same type.

Return the reformatted string
or return an empty string if it is impossible to reformat the string.

Example 1:
Input: s = "a0b1c2"
Output: "0a1b2c"
Explanation: No two adjacent characters have the same type in "0a1b2c". "a0b1c2", "0a1b2c", "0c2a1b" are also valid
permutations.

Example 2:
Input: s = "leetcode"
Output: ""
Explanation: "leetcode" has only characters so we cannot separate them by digits.

Example 3:
Input: s = "1229857369"
Output: ""
Explanation: "1229857369" has only digits so we cannot separate them by characters.

Example 4:
Input: s = "covid2019"
Output: "c2o0v1i9d"

Example 5:
Input: s = "ab123"
Output: "1a2b3"

Constraints:
1 <= s.length <= 500
s consists of only lowercase English letters and/or digits.
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
private:
    string construct(vector<char>& v1, vector<char>& v2) {
        string result = "";
        result.push_back(v1[0]);
        for (int i = 0; i < v2.size(); ++i) {
            result.push_back(v2[i]);
            if (i + 1 < v1.size()) {
                result.push_back(v1[i + 1]);
            }
        }
        return result;
    }

public:
    string reformat(string s) {
        vector<char> number;
        vector<char> letter;
        for (char c : s) {
            if (isdigit(c)) {
                number.push_back(c);
            } else {
                letter.push_back(c);
            }
        }

        int m = number.size();
        int n = letter.size();
        if (abs(m - n) > 1) {
            return "";
        }
        return m > n ? construct(number, letter) : construct(letter, number);
    }
};