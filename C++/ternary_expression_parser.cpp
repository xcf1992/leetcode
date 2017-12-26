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
using namespace std;


class Solution {
public:
    string parseTernary(string expression) {
        string result;
        stack<char> stk;
        for (int i = expression.size() - 1; i >= 0; i--) {
            char c = expression[i];
            if (!stk.empty() && stk.top() == '?') {
                stk.pop();
                char left = stk.top();
                stk.pop();
                stk.pop();
                char right = stk.top();
                stk.pop();
                if (c == 'T') {
                    stk.push(left);
                }
                else {
                    stk.push(right);
                }
            }
            else {
                stk.push(c);
            }
        }
        result.push_back(stk.top());
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}