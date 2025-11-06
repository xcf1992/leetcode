/*
415. Add Strings
https://leetcode.com/problems/add-strings/

Given two non-negative integers num1 and num2 represented as string,
return the sum of num1 and num2.

Note:
The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
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
    string addStrings(string num1, string num2) {
        string result = "";
        int i = num1.size() - 1;
        int j = num2.size() - 1;
        int carry = 0;
        while (i >= 0 or j >= 0 or carry > 0) {
            int sum = 0;
            if (carry > 0) {
                sum += carry;
            }
            if (i >= 0) {
                sum += num1[i] - '0';
                i -= 1;
            }
            if (j >= 0) {
                sum += num2[j] - '0';
                j -= 1;
            }
            carry = sum / 10;
            result.push_back(sum % 10 + '0');
        }
        reverse(result.begin(), result.end());
        return result;
    }
};