/*
 Implement a basic calculator to evaluate a simple expression string.
 
 The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.
 
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
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
private:
    bool IsOpt(char ch) {
        return  ch == '+' ||ch == '-' ||ch == '*' ||ch == '/';
    }
    
    int Calc(int num1, int num2, char opt) {
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
    
    void CalcTop(stack<int> &nums, stack<char> &opts) {
        int num2 = nums.top();
        nums.pop();
        
        int num1 = nums.top();
        nums.pop();
        
        char opt = opts.top();
        opts.pop();
        
        nums.push(Calc(num1, num2, opt));
    }
public:
    int calculate(string s) {
        stack<int> nums;
        stack<char> opts;
        int num = 0;
        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                num = num * 10 + s[i] - '0';
            }
            else if (IsOpt(s[i])) {
                nums.push(num);
                num = 0;
                if (s[i] == '+' || s[i] == '-') {
                    while (!opts.empty()) {
                        CalcTop(nums, opts);
                    }
                }
                else { // s[i] == '*' || s[i] == '/'
                    while (!opts.empty() && (opts.top() == '*'|| opts.top() == '/')) {
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
