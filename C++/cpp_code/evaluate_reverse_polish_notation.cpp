/*
150. Evaluate Reverse Polish Notation
https://leetcode.com/problems/evaluate-reverse-polish-notation/

Evaluate the value of an arithmetic expression in Reverse Polish Notation.
Valid operators are +, -, *, /.
Each operand may be an integer or another expression.

Note:
Division between two integers should truncate toward zero.
The given RPN expression is always valid.
That means the expression would always evaluate to a result and there won't be any divide by zero operation.

Example 1:
Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9

Example 2:
Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6

Example 3:
Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation:
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
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
using namespace std;

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        vector<int> calculator;
        for (unsigned int i = 0; i != tokens.size(); i++) {
            if (isdigit(tokens[i][0]) or tokens[i]
            .
            size() > 1
            )
            {
                calculator.push_back(stoi(tokens[i]));
                continue;
            }

            int operand1 = calculator.back();
            calculator.pop_back();
            int operand2 = calculator.back();
            calculator.pop_back();
            if (tokens[i] == "+") {
                calculator.push_back(operand2 + operand1);
            } else if (tokens[i] == "-") {
                calculator.push_back(operand2 - operand1);
            } else if (tokens[i] == "*") {
                calculator.push_back(operand2 * operand1);
            } else if (tokens[i] == "/") {
                calculator.push_back(operand2 / operand1);
            }
        }
        return calculator.back();
    }
};