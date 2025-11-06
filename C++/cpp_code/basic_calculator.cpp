/*
224. Basic Calculator
https://leetcode.com/problems/basic-calculator/

Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ),
the plus + or minus sign -, non-negative integers and empty spaces .

Example 1:
Input: "1 + 1"
Output: 2

Example 2:
Input: " 2-1 + 2 "
Output: 3

Example 3:
Input: "(1+(4+5+2)-3)+(6+8)"
Output: 23

Note:
You may assume that the given expression is always valid.
Do not use the eval built-in library function.
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
#include <set>
using namespace std;

class Solution {
private:
    int evaluate(string& s, int& i) {
        long res = 0;
        int positive = 1;
        while (i < s.size() and s[i] != ')') {
            if (s[i] == '+' or s[i] == ' ') {
                i++;
            } else if (s[i] == '-') {
                i++;
                positive = -1;
            } else if (s[i] == '(') {
                i++;
                res += positive * evaluate(s, i);
                positive = 1;
            } else {
                long num = 0;
                while (i < s.size() and isdigit(s[i])) {
                    num = num * 10 + s[i] - '0';
                    i += 1;
                }
                res += positive * num;
                positive = 1;
            }
        }
        i++;
        return res;
    }

public:
    int calculate(string s) {
        int pos = 0;
        return evaluate(s, pos);
    }
};