/*
65. Valid Number
Validate if a given string can be interpreted as a decimal number.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3   " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false

Note: It is intended for the problem statement to be ambiguous.
You should gather all requirements up front before implementing one.
However, here is a list of characters that can be in a valid decimal number:

Numbers 0-9
Exponent - "e"
Positive/negative sign - "+"/"-"
Decimal point - "."
Of course, the context of these characters also matters in the input.

Update (2015-02-10):
The signature of the C++ function had been updated.
If you still see your function signature accepts a const char * argument,
please click the reload button to reset your code definition.
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
using namespace std;

// https://leetcode.com/problems/valid-number/discuss/23725/C%2B%2B-My-thought-with-DFA
class Solution {
public:
    bool isNumber(string str) {
        while (str[0] == ' ') {
            str.erase(0, 1);  // delete the  prefix whitespace
        }
        while (str[str.length() - 1] == ' ') {
            str.erase(str.length() - 1, 1);  // delete the suffix whitespace
        }

        int state = 0;
        int flag = 0;  // flag to judge the special case "."
        for (int i = 0; i < str.length(); i++) {
            if (isdigit(str[i])) {
                flag = 1;
                if (state <= 2) {
                    state = 2;
                } else {
                    state = (state <= 5) ? 5 : 7;
                }
            } else if ('+' == str[i] or '-' == str[i]) {
                if (state == 0 or state == 3) {
                    state++;
                } else {
                    return false;
                }
            } else if ('.' == str[i]) {
                if (state <= 2) {
                    state = 6;
                } else {
                    return false;
                }
            } else if ('e' == str[i]) {
                if (flag and (state == 2 or state == 6 or state == 7)) {
                    state = 3;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        return state == 2 or state == 5 or (flag and state == 6) or state == 7;
    }
};