/*
 282. Expression Add Operators

 Given a string that contains only digits 0-9 and a target value,
 return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

 Example 1:

 Input: num = "123", target = 6
 Output: ["1+2+3", "1*2*3"]
 Example 2:

 Input: num = "232", target = 8
 Output: ["2*3+2", "2+3*2"]
 Example 3:

 Input: num = "105", target = 5
 Output: ["1*0+5","10-5"]
 Example 4:

 Input: num = "00", target = 0
 Output: ["0+0", "0-0", "0*0"]
 Example 5:

 Input: num = "3456237490", target = 9191
 Output: []
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
    // cur: {string} expression generated so far.
    // pos: {int}    current visiting position of num.
    // cv:  {long}   cumulative value so far.
    // pv:  {long}   previous operand value.
    // op:  {char}   previous operator used.
    void dfs(vector<string>& result, string& num, int& target, string cur, int pos, long cv, long pv, char op) {
        if (pos == num.size() and cv == target) {
            result.push_back(cur);
            return;
        }

        for (int i = pos + 1; i <= num.size(); i++) {
            string newStr = num.substr(pos, i - pos);
            long newVal = stol(newStr);
            if (to_string(newVal).size() != newStr.size()) {
                continue;
            }
            dfs(result, num, target, cur + "+" + newStr, i, cv + newVal, newVal, '+');
            dfs(result, num, target, cur + "-" + newStr, i, cv - newVal, newVal, '-');
            // we will consider all the * sequence as one group, so we will pass down the previous operator op
            if (op == '+') {
                dfs(result, num, target, cur + "*" + newStr, i, cv - pv + pv * newVal, pv * newVal, op);
            }
            else if (op == '-') {
                dfs(result, num, target, cur + "*" + newStr, i, cv + pv - pv * newVal, pv * newVal, op);
            }
            else {
                // this will only happen we first assign a sequence of * operations from beginning
                dfs(result, num, target, cur + "*" + newStr, i, pv * newVal, pv * newVal, op);
            }
        }
    }
public:
    vector<string> addOperators(string num, int target) {
        int n = num.size();
        if (n == 0) {
            return {};
        }

        vector<string> result;
        for (int i = 1; i <= n; i++) {
            string cur = num.substr(0, i);
            long curVal = stol(cur);
            if (to_string(curVal).size() != cur.size()) {
                continue;
            }
            // no operator defined.
            dfs(result, num, target, cur, i, curVal, curVal, '#');
        }
        return result;
    }
};
