/*
 770. Basic Calculator IV
 Given an expression such as expression = "e + 8 - a + 5" and an evaluation map such as {"e": 1} (given in terms of evalvars = ["e"] and evalints = [1]), return a list of tokens representing the simplified expression, such as ["-1*a","14"]

 An expression alternates chunks and symbols, with a space separating each chunk and symbol.
 A chunk is either an expression in parentheses, a variable, or a non-negative integer.
 A variable is a string of lowercase letters (not including digits.) Note that variables can be multiple letters, and note that variables never have a leading coefficient or unary operator like "2x" or "-x".
 Expressions are evaluated in the usual order: brackets first, then multiplication, then addition and subtraction. For example, expression = "1 + 2 * 3" has an answer of ["7"].

 The format of the output is as follows:

 For each term of free variables with non-zero coefficient, we write the free variables within a term in sorted order lexicographically. For example, we would never write a term like "b*a*c", only "a*b*c".
 Terms have degree equal to the number of free variables being multiplied, counting multiplicity. (For example, "a*a*b*c" has degree 4.) We write the largest degree terms of our answer first, breaking ties by lexicographic order ignoring the leading coefficient of the term.
 The leading coefficient of the term is placed directly to the left with an asterisk separating it from the variables (if they exist.)  A leading coefficient of 1 is still printed.
 An example of a well formatted answer is ["-2*a*a*a", "3*a*a*b", "3*b*b", "4*a", "5*c", "-6"]
 Terms (including constant terms) with coefficient 0 are not included.  For example, an expression of "0" has an output of [].
 Examples:

 Input: expression = "e + 8 - a + 5", evalvars = ["e"], evalints = [1]
 Output: ["-1*a","14"]

 Input: expression = "e - 8 + temperature - pressure",
 evalvars = ["e", "temperature"], evalints = [1, 12]
 Output: ["-1*pressure","5"]

 Input: expression = "(e + 8) * (e - 8)", evalvars = [], evalints = []
 Output: ["1*e*e","-64"]

 Input: expression = "7 - 7", evalvars = [], evalints = []
 Output: []

 Input: expression = "a * b * c + b * a * c * 4", evalvars = [], evalints = []
 Output: ["5*a*b*c"]

 Input: expression = "((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))",
 evalvars = [], evalints = []
 Output: ["-1*a*a*b*b","2*a*a*b*c","-1*a*a*c*c","1*a*b*b*b","-1*a*b*b*c","-1*a*b*c*c","1*a*c*c*c","-1*b*b*b*c","2*b*b*c*c","-1*b*c*c*c","2*a*a*b","-2*a*a*c","-2*a*b*b","2*a*c*c","1*b*b*b","-1*b*b*c","1*b*c*c","-1*c*c*c","-1*a*a","1*a*b","1*a*c","-1*b*c"]
 Note:

 expression will have length in range [1, 250].
 evalvars, evalints will have equal lengths in range [0, 100].
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
public:
    bool isNumber(string& s) {
        return s.back() >= '0' && s.back() <= '9';
    }

    bool isVariable(string& s) {
        return s[0] >= 'a' && s[0] <= 'z';
    }

    int priority(string& s) {
        if (s == "+") return 1;
        if (s == "-") return 1;
        if (s == "*") return 2;
        return -1; // "("
    }

    bool equal(vector<string>& a, vector<string>& b) {
        if (a.size() != b.size()) return false;
        for (int i = 1; i < a.size(); i++) if (a[i] != b[i]) return false;
        return true;
    }

    vector<vector<string>> calculate(vector<vector<string>>& a, string& opr, vector<vector<string>>& b) {
        // input:
        // `a` and `b`: [[1,e,e], [-64]], [[-1,pressure], [5]] --- such vector<vector<string>>
        // `opr`: "+" or "-" or "*"
        // output:
        // [[1,e,e], [-1,pressure], [-59]]: the calculated and sorted and merged polynomials
        vector<vector<string>> c;
        if (opr == "+") {
            for (auto& s : a) c.push_back(s);
            for (auto& s : b) c.push_back(s);
        } else if (opr == "-") {
            for (auto& s : a) c.push_back(s);
            for (auto& s : b) {
                c.push_back(s);
                c.back()[0] = to_string(-stoi(c.back()[0]));
            }
        } else {
            for (auto& s : a) {
                for (auto& t : b) {
                    // multiply s and t
                    vector<string> o;
                    o.push_back(to_string(stoi(s[0]) * stoi(t[0])));
                    for (int i = 1; i < s.size(); i++) o.push_back(s[i]);
                    for (int i = 1; i < t.size(); i++) o.push_back(t[i]);
                    c.push_back(o);
                }
            }
        }

        // merge and sort the result

        // 1. sort every "*" expression
        for (auto& s : c) {
            sort(s.begin() + 1, s.end());
        }
        // 2. sort the "*" expressions
        sort(c.begin(), c.end(), [](auto& p, auto& q) {
            if (p.size() != q.size()) return p.size() > q.size();
            for (int i = 1; i < p.size(); i++) {
                if (p[i] != q[i]) return p[i] < q[i];
            }
            return true;
        });
        // 3. merge the "*" expressions
        vector<vector<string>> result;
        for (auto& s : c) {
            if (!result.empty() && equal(result.back(), s)) {
                result.back()[0] = to_string(stoi(result.back()[0]) + stoi(s[0]));
            } else {
                result.push_back(s);
            }
            if (result.back()[0] == "0") result.pop_back();
        }
        return result;
    }

    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        // split into symbols, each symbol is "(" or ")" or a number or a variable or a operator.
        vector<string> v(1);
        for (char c : expression) {
            if (c == '(' || c == ')') {
                if (!v.back().empty()) v.push_back(string());
                v.back() += c;
                v.push_back(string());
            } else if (c == ' ') {
                if (!v.back().empty()) v.push_back(string());
            } else {
                v.back() += c;
            }
        }
        if (v.back().empty()) v.pop_back();
        // for (auto s : v) cout << s << endl;

        // store evalvars in a hash table
        unordered_map<string, int> m;
        for (int i = 0; i < evalvars.size(); i++) {
            m[evalvars[i]] = evalints[i];
        }

        // replace the evalvars in `v`
        for (auto& s : v) {
            if (m.find(s) != m.end()) {
                s = to_string(m[s]);
            }
        }

        // convert to RPN
        // for example: 5 * (a - b) + c ==> 5 a b - * c +
        v.push_back(")");
        stack<string> st;
        st.push("(");
        vector<string> u;
        for (auto& s : v) {
            if (isNumber(s) || isVariable(s)) {
                u.push_back(s);
            } else if (s == "(") {
                st.push(s);
            } else if (s == ")") {
                while (st.top() != "(") {
                    u.push_back(st.top());
                    st.pop();
                }
                st.pop();
            } else {
                int p = priority(s);
                while (priority(st.top()) >= p) {
                    u.push_back(st.top());
                    st.pop();
                }
                st.push(s);
            }
        }
        // for (auto s : u) cout << s << endl;

        // calculate the RPN
        // each element in the stack is, for example, [[12, a, b, b] + [-2333, b, c] + ... + [233]]
        stack<vector<vector<string>>> ste; // stack of expressions
        for (auto& s : u) {
            if (isNumber(s)) {
                ste.push(vector<vector<string>>(1, vector<string>(1, s)));
            } else if (isVariable(s)) {
                ste.push(vector<vector<string>>(1, vector<string>(2, s)));
                ste.top()[0][0] = "1";
            } else {
                auto second = ste.top();
                ste.pop();
                auto first = ste.top();
                ste.pop();
                ste.push(calculate(first, s, second));
            }
        }

        // convert to vector<string>
        // the result is, for example, ["12*a*b*b", "-2333*b*c", ......, "233"]
        auto r = ste.top();
        vector<string> result;
        for (auto& p : r) {
            if (p[0] == "0") continue;
            result.push_back(string());
            for (auto& q : p) {
                result.back() += q + "*";
            }
            result.back().pop_back();
        }
        return result;
    }
};
