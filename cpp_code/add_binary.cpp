/*
67. Add Binary
Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        int m = a.size();
        int n = b.size();
        if (m < n) {
            return addBinary(b, a);
        }
        if (n == 0) {
            return a;
        }

        string result = "";
        int carry = 0;
        for (int i = 0; i < m; i++) {
            int sum = carry + (a[m - 1 - i] - '0');
            if (i < n) {
                sum += (b[n - 1 - i] - '0');
            }
            carry = sum / 2;
            result.push_back('0' + sum % 2);
        }
        if (carry) {
            result.push_back('1');
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
