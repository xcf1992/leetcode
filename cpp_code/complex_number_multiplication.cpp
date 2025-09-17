/*
537. Complex Number Multiplication
Given two strings representing two complex numbers.

You need to return a string representing their multiplication.
Note i2 = -1 according to the definition.

Example 1:
Input: "1+1i", "1+1i"
Output: "0+2i"
Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
Example 2:
Input: "1+-1i", "1+-1i"
Output: "0+-2i"
Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
Note:

The input strings will not have extra blank.
The input strings will be given in the form of a+bi,
where the integer a and b will both belong to the range of [-100, 100].
And the output should be also in this form.
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
    pair<int, int> decode(string number) {
        int pos = number.find("+");
        string part1 = number.substr(0, pos);
        string part2 = number.substr(pos + 1, number.find("i") - pos - 1);
        return {stoi(part1), stoi(part2)};
    }
public:
    string complexNumberMultiply(string a, string b) {
        pair<int, int> factor1 = decode(a);
        pair<int, int> factor2 = decode(b);
        string s1 = to_string(factor1.first * factor2.first - factor1.second * factor2.second);
        string s2 = to_string(factor1.second * factor2.first + factor1.first * factor2.second);
        return s1 + "+" + s2 + "i";
    }
};
