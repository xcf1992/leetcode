#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
using namespace std;

int longestValidParentheses(string s) {
        if (s.size() <= 1) {
            return s.size();
        }
        
        stack<int> stk;
        int result = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                stk.push(i);
            }
            else {
                if (s.empty()) {
                    stk.push(i);
                }
                else if (s[stk.top()] == ')') {
                    stk.push(i);
                }
                else {
                    stk.pop();
                    if (stk.empty()) {
                        result = max(result, i + 1);
                    }
                    else {
                        result = max(result, i - stk.top());
                    }
                }
            }
        }
        
        return result;
    }
int main() {
	string s = "((()))())";
	longestValidParentheses(s);
	return 0;
}