
/*
166. Fraction to Recurring Decimal
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

Example 1:

Input: numerator = 1, denominator = 2
Output: "0.5"
Example 2:

Input: numerator = 2, denominator = 1
Output: "2"
Example 3:

Input: numerator = 2, denominator = 3
Output: "0.(6)"
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) {
            return "0";
        }
        if (numerator == denominator) {
            return "1";
        }

        bool negative = (numerator > 0) ^ (denominator > 0);
        long long quotient = 0;
        long long dmt = labs(denominator);
        long long rest = labs(numerator);
        string result = "";
        if (rest > dmt) {
            quotient = rest / dmt;
            rest = rest % dmt;
            result = to_string(quotient);
            if (rest == 0) {
                return negative ? "-" + result : result;
            }
        }
        else {
            result += "0";
        }
        result += ".";

        int pos = result.size();
        unordered_map<int, int> restNum;
        while (restNum.find(rest) == restNum.end()) {
            restNum[rest] = pos;
            pos++;

            rest *= 10;
            result = result + to_string(rest / dmt);
            rest = rest % dmt;
            if (rest == 0) {
                return negative ? "-" + result : result;
            }
        }
        string recur = result.substr(restNum[rest]);
        result = result.substr(0, restNum[rest]) + "(" + recur + ")";
        return negative ? "-" + result : result;
    }
};
