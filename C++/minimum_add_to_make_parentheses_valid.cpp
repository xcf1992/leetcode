/*
921. Minimum Add to Make Parentheses Valid
https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/

Given a string S of '(' and ')' parentheses,
we add the minimum number of parentheses ( '(' or ')', and in any positions )
so that the resulting parentheses string is valid.

Formally, a parentheses string is valid if and only if:
It is the empty string, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
Given a parentheses string, return the minimum number of parentheses we must add to make the resulting string valid.

Example 1:
Input: "())"
Output: 1

Example 2:
Input: "((("
Output: 3

Example 3:
Input: "()"
Output: 0

Example 4:
Input: "()))(("
Output: 4

Note:
S.length <= 1000
S only consists of '(' and ')' characters.
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
public:
    int minAddToMakeValid(string S) {
        int result = 0;
        int left = 0;
        int right = 0;
        for (char c : S) {
            if (c == '(') {
                left += 1;
            }
            else if (c == ')') {
                right += 1;
                if (left < right) {
                    left += 1;
                    result += 1;
                }
            }
        }
        return result + abs(left - right);
    }
};
