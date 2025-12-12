/*
227. Basic Calculator II

Implement a basic calculator to evaluate a simple expression string.
The expression string contains only non-negative integers, +, -, *, / operators and empty spaces.
The integer division should truncate toward zero.

Example 1:
Input: "3+2*2"
Output: 7

Example 2:
Input: " 3/2 "
Output: 1

Example 3:
Input: " 3+5 / 2 "
Output: 5

Note:
You may assume that the given expression is always valid.
Do not use the eval built-in library function.
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
#include <climits>
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    long parse_num(string& s, int& i) {
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
        for (; i < s.size() and op != ')'; ++i) {
            // when op becomes ), we will still have ++i, and skip it and jump back to upper level
            if (s[i] == ' ') {
                continue;
            }

            long n = s[i] == '(' ? parseExp(s, ++i) : parse_num(s, i);
            if (op == '+') {
                nums.push_back(n);
            } else if (op == '-') {
                nums.push_back(-n);
            } else if (op == '*') {
                nums.back() *= n;
            } else if (op == '/') {
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

class Solution1 {
private:
    bool isOpt(char c) {
        return c == '+' or c == '-' or c == '*' or c == '/';
    }

public:
    int calculate(string s) {
        int n = s.size();
        if (n == 0) {
            return 0;
        }

        int num = 0;
        vector<int> stk;
        char op = '+';
        for (int i = 0; i < n; ++i) {
            if (isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
            }
            if (isOpt(s[i]) or i == n - 1) {
                // we have to use if rather than elseif here, cause we want to go into it when i == n - 1
                if (op == '+') {
                    stk.push_back(num);
                }
                if (op == '-') {
                    stk.push_back(0 - num);
                }
                if (op == '*') {
                    int tmp = stk.back();
                    stk.pop_back();
                    stk.push_back(tmp * num);
                }
                if (op == '/') {
                    int tmp = stk.back();
                    stk.pop_back();
                    stk.push_back(tmp / num);
                }
                op = s[i];
                num = 0;
            }
        }
        return accumulate(stk.begin(), stk.end(), 0);
    }
};

class Solution2 {
private:
    bool IsOpt(char ch) {
        return ch == '+' or ch == '-' or ch == '*' or ch == '/';
    }

    long Calc(long num1, long num2, char opt) {
        if (opt == '+') {
            return num1 + num2;
        }
        if (opt == '-') {
            return num1 - num2;
        }
        if (opt == '*') {
            return num1 * num2;
        }
        return num1 / num2;
    }

    void CalcTop(stack<long>& nums, stack<char>& opts) {
        long num2 = nums.top();
        nums.pop();

        long num1 = nums.top();
        nums.pop();

        char opt = opts.top();
        opts.pop();

        nums.push(Calc(num1, num2, opt));
    }

public:
    int calculate(string s) {
        stack<long> nums;
        stack<char> opts;
        long num = 0;
        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                num = num * 10 + s[i] - '0';
            } else if (IsOpt(s[i])) {
                nums.push(num);
                num = 0;
                if (s[i] == '+' or s[i] == '-') {
                    while (!opts.empty()) {
                        CalcTop(nums, opts);
                    }
                } else {
                    // s[i] == '*' or s[i] == '/'
                    while (!opts.empty() and (opts.top() == '*' or opts.top() == '/')) {
                        CalcTop(nums, opts);
                    }
                }
                opts.push(s[i]);
            }
        }

        nums.push(num);
        while (!opts.empty()) {
            CalcTop(nums, opts);
        }
        return nums.top();
    }
};