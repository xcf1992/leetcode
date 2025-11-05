/*
1307. Verbal Arithmetic Puzzle
https://leetcode.com/problems/verbal-arithmetic-puzzle/

Given an equation, represented by words on left side and the result on right side.

You need to check if the equation is solvable under the following rules:
Each character is decoded as one digit (0 - 9).
Every pair of different characters they must map to different digits.
Each words[i] and result are decoded as one number without leading zeros.
Sum of numbers on left side (words) will equal to the number on right side (result).
Return True if the equation is solvable otherwise return False.

Example 1:
Input: words = ["SEND","MORE"], result = "MONEY"
Output: true
Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652

Example 2:
Input: words = ["SIX","SEVEN","SEVEN"], result = "TWENTY"
Output: true
Explanation: Map 'S'-> 6, 'I'->5, 'X'->0, 'E'->8, 'V'->7, 'N'->2, 'T'->1, 'W'->'3', 'Y'->4
Such that: "SIX" + "SEVEN" + "SEVEN" = "TWENTY" ,  650 + 68782 + 68782 = 138214

Example 3:
Input: words = ["THIS","IS","TOO"], result = "FUNNY"
Output: true

Example 4:
Input: words = ["LEET","CODE"], result = "POINT"
Output: false

Constraints:
2 <= words.length <= 5
1 <= words[i].length, results.length <= 7
words[i], result contains only upper case English letters.
Number of different characters used on the expression is at most 10.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <map>
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    unordered_map<char, int> c2i;
    unordered_map<int, char> i2c;
    int limit = 0; // length of result

    /*
    * digit: index of digit in a word
    * widx: index of a word in word list
    * sum: summation of all word[digit]
    */
    bool check(vector<string> &words, string &result, int digit, int widx, int sum) {
        if (digit == limit) {
            return sum == 0;
        }

        if (widx == words.size()) {
            if (c2i.find(result[digit]) == c2i.end() and
            i2c.find(sum % 10) == i2c.end()
            )
            {
                if (sum % 10 == 0 and digit
                +1 == limit
                )
                {
                    return false; // avoid leading zero in result
                }
                c2i[result[digit]] = sum % 10;
                i2c[sum % 10] = result[digit];
                bool valid = check(words, result, digit + 1, 0, sum / 10);
                c2i.erase(result[digit]);
                i2c.erase(sum % 10);
                return valid;
            }
            if (c2i.find(result[digit]) != c2i.end() and c2i[result[digit]]
            ==
            sum % 10
            )
            {
                return check(words, result, digit + 1, 0, sum / 10);
            }
            return false;
        }

        // if word[widx] length less than digit, ignore and go to next word
        if (digit >= words[widx].size()) {
            return check(words, result, digit, widx + 1, sum);
        }

        // if word[widx][digit] already mapped to a value
        if (c2i.find(words[widx][digit]) != c2i.end()) {
            if (digit + 1 == words[widx].length() and words[widx]
            .
            size() > 1
            and c2i[words[widx][digit]]
            ==
            0
            )
            {
                return false;
            }
            return check(words, result, digit, widx + 1, sum + c2i[words[widx][digit]]);
        }

        // if word[widx][digit] not mapped to a value yet
        for (int i = 0; i < 10; ++i) {
            if (digit + 1 == words[widx].length() && i == 0 && words[widx].length() > 1) {
                continue;
            }
            if (i2c.count(i)) {
                continue;
            }

            c2i[words[widx][digit]] = i;
            i2c[i] = words[widx][digit];
            bool tmp = check(words, result, digit, widx + 1, sum + i);
            c2i.erase(words[widx][digit]);
            i2c.erase(i);
            if (tmp) {
                return true;
            }
        }
        return false;
    }

public:
    bool isSolvable(vector<string> &words, string result) {
        limit = result.size();
        for (string &word: words) {
            if (word.size() > limit) {
                return false;
            }
            reverse(word.begin(), word.end());
        }
        reverse(result.begin(), result.end());
        return check(words, result, 0, 0, 0);
    }
};