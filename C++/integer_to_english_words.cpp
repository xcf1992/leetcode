/*
273. Integer to English Words
https://leetcode.com/problems/integer-to-english-words/

Convert a non-negative integer to its english words representation.
Given input is guaranteed to be less than 2^31 - 1.

Example 1:
Input: 123
Output: "One Hundred Twenty Three"

Example 2:
Input: 12345
Output: "Twelve Thousand Three Hundred Forty Five"

Example 3:
Input: 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

Example 4:
Input: 1234567891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
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
    vector<string> below20 = vector<string>({"One", "Two", "Three", "Four","Five","Six","Seven","Eight","Nine","Ten", "Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"});
    vector<string> below100 = vector<string>({"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"});

    string int2string(int num) {
        if (num >= 1000000000) {
            return int2string(num / 1000000000) + " Billion" + int2string(num % 1000000000);
        }

        if (num >= 1000000) {
            return int2string(num / 1000000) + " Million" + int2string(num % 1000000);
        }

        if (num >= 1000) {
            return int2string(num / 1000) + " Thousand" + int2string(num % 1000);
        }

        if (num >= 100) {
            return int2string(num / 100) + " Hundred" + int2string(num % 100);
        }

        if (num >= 20) {
            return " " + below100[num / 10 - 2] + int2string(num % 10);
        }

        if (num >= 1){
            return " " + below20[num - 1];
        }
        return ""; // this cannot be removed, otherwis test case 20 will fail
    }
public:
    string numberToWords(int num) {
        if (num == 0) {
            return "Zero";
        }
        return int2string(num).substr(1);
    }
};
