/*
1271. Hexspeak
https://leetcode.com/problems/hexspeak/

A decimal number can be converted to its Hexspeak representation by first converting it to an uppercase hexadecimal
string, then replacing all occurrences of the digit 0 with the letter O, and the digit 1 with the letter I. Such a
representation is valid if and only if it consists only of the letters in the set {"A", "B", "C", "D", "E", "F", "I",
"O"}.

Given a string num representing a decimal integer N,
return the Hexspeak representation of N if it is valid,
otherwise return "ERROR".

Example 1:
Input: num = "257"
Output: "IOI"
Explanation:  257 is 101 in hexadecimal.

Example 2:
Input: num = "3"
Output: "ERROR"

Constraints:
1 <= N <= 10^12
There are no leading zeros in the given string.
All answers must be in uppercase letters.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    string toHexspeak(string num) {
        vector<string> digit({"O", "I", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"});
        long long val = stoll(num);
        string hex = "";
        bool valid = true;
        while (val != 0) {
            int cur = val % 16;
            hex += digit[cur];
            if (hex.back() >= '2' and hex.back() <= '9') {
                valid = false;
                break;
            }
            val /= 16;
        }

        if (!valid) {
            return "ERROR";
        }
        reverse(hex.begin(), hex.end());
        return hex;
    }
};