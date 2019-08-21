/*
592. Fraction Addition and Subtraction
Given a string representing an expression of fraction addition and subtraction,
you need to return the calculation result in string format.
The final result should be irreducible fraction.
If your final result is an integer, say 2,
you need to change it to the format of fraction that has denominator 1.
So in this case, 2 should be converted to 2/1.

Example 1:
Input:"-1/2+1/2"
Output: "0/1"

Example 2:
Input:"-1/2+1/2+1/3"
Output: "1/3"

Example 3:
Input:"1/3-1/2"
Output: "-1/6"

Example 4:
Input:"5/3+1/3"
Output: "2/1"

Note:
The input string only contains '0' to '9', '/', '+' and '-'.
So does the output.

Each fraction (input and output) has format ±numerator/denominator.
If the first input fraction or the output is positive, then '+' will be omitted.

The input only contains valid irreducible fractions,
where the numerator and denominator of each fraction will always be in the range [1,10].
If the denominator is 1, it means this fraction is actually an integer in a fraction format defined above.

The number of given fractions will be in the range [1,10].

The numerator and denominator of the final result are guaranteed to be valid and in the range of 32-bit int.
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
    int getGCD(int a, int b) {
        if (a < b) {
            return getGCD(b, a);
        }
        return b == 0 ? a : getGCD(b, a % b);
    }

    int getLCM(int a, int b) {
        return a == 0 || b == 0 ? 0 : a * b / getGCD(a, b);
    }
public:
    string fractionAddition(string expression) {
        int n = 0;
        int d = 1;
        int p = 1;

        int i = 0;
        while (i < expression.size()) {
            int n1 = 0;
            int d1 = 0;
            int p1 = 1;
            if (expression[i] == '-') {
                p1 = -1;
                i++;
            }
            else if (expression[i] == '+') {
                i++;
            }

            while (isdigit(expression[i])) {
                n1 = n1 * 10 + (expression[i] - '0');
                i++;
            }

            i++;

            while (isdigit(expression[i]) and i < expression.size()) {
                d1 = d1 * 10 + (expression[i] - '0');
                i++;
            }

            int lcm = getLCM(d, d1);
            int newn = p * n * (lcm / d) + p1 * n1 * (lcm / d1);
            d = lcm;
            if (newn >= 0) {
                p = 1;
                n = newn;
            }
            else {
                p = -1;
                n = 0 - newn;
            }
        }

        int gcd = getGCD(n, d);
        string result = p == 1 ? "" : "-";
        return result + to_string(n / gcd) + "/" + to_string(d / gcd);
    }
};
