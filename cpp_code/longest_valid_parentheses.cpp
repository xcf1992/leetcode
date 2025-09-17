/*
32. Longest Valid Parentheses

Given a string containing just the characters '(' and ')',
find the length of the longest valid (well-formed) parentheses substring.

Example 1:
Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"

Example 2:
Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        int result = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                stk.push(i);
            }
            else {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i);
                }
                else {
                    result = max(result, i - stk.top());
                }
            }
        }
        return result;
    }
};

class Solution1 { // two pass
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        int result = 0;
        int left = 0;
        int right = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                left +=1;
            }
            else {
                right += 1;
            }
            if (left == right) {
                result = max(result, left * 2);
            }
            else if (right >= left) {
                left = right = 0;
            }
        }

        left = right = 0;
        for (int i = n - 1; i>= 0; --i) {
            if (s[i] == '(') {
                left += 1;
            }
            else {
                right += 1;
            }
            if (right == left) {
                result = max(result, 2 * left);
            }
            else if (left >= right) {
                left = right = 0;
            }
        }
        return result;
    }
};
