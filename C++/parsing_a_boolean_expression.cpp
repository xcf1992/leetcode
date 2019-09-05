/*
1106. Parsing A Boolean Expression
Return the result of evaluating a given boolean expression, represented as a string.

An expression can either be:

"t", evaluating to True;
"f", evaluating to False;
"!(expr)", evaluating to the logical NOT of the inner expression expr;
"&(expr1,expr2,...)", evaluating to the logical AND of 2 or more inner expressions expr1, expr2, ...;
"|(expr1,expr2,...)", evaluating to the logical OR of 2 or more inner expressions expr1, expr2, ...


Example 1:

Input: expression = "!(f)"
Output: true
Example 2:

Input: expression = "|(f,t)"
Output: true
Example 3:

Input: expression = "&(t,f)"
Output: false
Example 4:

Input: expression = "|(&(t,f,t),!(t))"
Output: false


Constraints:

1 <= expression.length <= 20000
expression[i] consists of characters in {'(', ')', '&', '|', '!', 't', 'f', ','}.
expression is a valid expression representing a boolean, as given in the description.
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
private:
    bool parse(string& expression, int& pos) {
        int n = expression.size();
        if (pos >= n) {
            return true;
        }

        char op = ' ';
        vector<bool> vals;
        while (pos < n and expression[pos] != ')') {
            if (expression[pos] == '!' or expression[pos] == '&' or expression[pos] == '|') {
                if (op == ' ') {
                    op = expression[pos];
                }
                else {
                    vals.push_back(parse(expression, pos));
                }
            }
            else if (expression[pos] == 't' or expression[pos] == 'f') {
                vals.push_back('t' == expression[pos]);
            }
            pos += 1;
        }

        if (op == '!') {
            return !vals[0];
        }
        while (vals.size() > 1) {
            bool v1 = vals.back();
            vals.pop_back();
            bool v2 = vals.back();
            vals.pop_back();
            if (op == '&') {
                vals.push_back(v1 and v2);
            }
            else {
                vals.push_back(v1 or v2);
            }
        }
        return vals[0];
    }
public:
    bool parseBoolExpr(string expression) {
        int pos = 0;
        return parse(expression, pos);
    }
};

class Solution1 { // stack
public:
    bool parseBoolExpr(string expr) {
        stack<char> val, op;
        for (char ch : expr) {
            if (ch == 't' or ch == 'f' or ch == '(') {
                val.push(ch);
            }
            else if (ch == '&' or ch == '|' or ch == '!') {
                op.push(ch);
            }
            else if (ch == ')') {
                char p = op.top();
                op.pop();
                bool v = (val.top() == 't');
                val.pop();

                if (p == '!') { // Negate the value for ! operator
                    v = !v;
                }
                while (val.top() != '(') { // Keep popping the values till the top element is (
                    if (p == '&') {
                        v = v and (val.top() == 't');
                    }
                    else {
                        v = v or (val.top() == 't');
                    }
                    val.pop();
                }
                val.pop(); // This pop is needed to pop the (
                val.push(v ? 't' : 'f');
            }
        }
        return val.top() == 't'; // Return the final result by converting it to a bool value
    }
};
