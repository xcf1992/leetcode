/*
772. Basic Calculator III

Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ),
the plus + or minus sign -,
non-negative integers and empty spaces .

The expression string contains only non-negative integers, +, -, *, / operators ,
open ( and closing parentheses ) and empty spaces .
The integer division should truncate toward zero.

You may assume that the given expression is always valid.
All intermediate results will be in the range of [-2147483648, 2147483647].

Some examples:
"1 + 1" = 2
" 6-4 / 2 " = 4
"2*(5+5*2)/3+(6/2+8)" = 21
"(2+6* 3+5- (3*14/7+2)*5)+3"=-12

Note:
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
private:
    long parseNum(string& s, int& i) {
        long num = 0;
        while (i < s.size() and isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
            i += 1;
        }
        return num;
    }

    int parseExp(string& s, int& i) {
        vector<int> nums;
        char op = '+';
        for (; i < s.size() and op != ')'; ++i) { // when op becomes ), we will still have ++i, and skip it and jump back to upper level
            if (s[i] == ' ') {
                continue;
            }

            long n = s[i] == '(' ? parseExp(s, ++i) : parseNum(s, i);
            if (op == '+') {
                nums.push_back(n);
            }
            else if (op == '-') {
                nums.push_back(-n);
            }
            else if (op == '*') {
                nums.back() *= n;
            }
            else if (op == '/') {
                nums.back() /= n;
            }

            if (i < s.size()) {
                op = s[i];
            }
        }
        return accumulate(nums.begin(), nums.end(), 0);
    }
public:
    int calculate(string s) {
        int i = 0;
        return parseExp(s, i);
    }
};
