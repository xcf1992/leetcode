/*
20. Valid Parentheses
https://leetcode.com/problems/valid-parentheses/

Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

An input string is valid if:
Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:
Input: "()"
Output: true

Example 2:
Input: "()[]{}"
Output: true

Example 3:
Input: "(]"
Output: false

Example 4:
Input: "([)]"
Output: false

Example 5:
Input: "{[]}"
Output: true
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
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
    bool isPaired(stack<char>& stk, char c) {
        if (stk.empty()) {
            return false;
        }
        if (c == ')' and stk.top() == '(') {
            return true;
        }
        if (c == '}' and stk.top() == '{') {
            return true;
        }
        if (c == ']' and stk.top() == '[') {
            return true;
        }
        return false;
    }
public:
    bool isValid(string s) {
        stack<char> stk;
        for (char c : s) {
            if (c == '(' or c == '{' or c == '[') {
                stk.push(c);
                continue;
            }

            if (!isPaired(stk, c)) {
                return false;
            }
            stk.pop();
        }
        return stk.empty();
    }
};
