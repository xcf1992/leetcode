/*
 Implement a basic calculator to evaluate a simple expression string.
 
 The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .
 
 You may assume that the given expression is always valid.
 
 Some examples:
 "1 + 1" = 2
 " 2-1 + 2 " = 3
 "(1+(4+5+2)-3)+(6+8)" = 23
 Note: Do not use the eval built-in library function.
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
public:
    int calculate(string s) {
        int pos = 0;
        return evaluate(s,pos);
    }
    
    int evaluate(string& s, int& i) {
        int res = 0;
        bool negFlag = false;
        while (i < s.size() && s[i] != ')') {
            if (s[i] == '+' || s[i] == ' ')
                i++;
            else if (s[i] == '-') {
                i++;
                negFlag = true;
            }
            else if (s[i] == '(') {
                i++;
                res += negFlag ? 0 - evaluate(s,i) : evaluate(s,i);
                negFlag = false;
            }
            else {
                int num = 0;
                while (i < s.size() && isdigit(s[i])) {
                    num = num * 10 + s[i]-'0';
                    i += 1;
                }
                res += negFlag ? 0 - num : num;
                negFlag = false;
            }
        }
        i++;
        return res;
    }
};
