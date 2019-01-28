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
            if (op == '+') {
                dfs(result, num, target, cur + "*" + newStr, i, cv - pv + pv * newVal, pv * newVal, op);
            }
            else if (op == '-') {
                dfs(result, num, target, cur + "*" + newStr, i, cv + pv - pv * newVal, pv * newVal, op);
            }
            else {
                dfs(result, num, target, cur + "*" + newStr, i, pv * newVal, pv * newVal, op);
            }
        }
    }
public:
    vector<string> addOperators(string num, int target) {
        int n = num.size();
        vector<string> result;
        if (n == 0) {
            return result;
        }

        for (int i = 1; i <= n; i++) {
            string s = num.substr(0, i);
            long cur = stol(s);
            if (to_string(cur).size() != s.size()) {
                continue;
            }
            dfs(result, num, target, s, i, cur, cur, '#');
        }
        return result;
    }
};

int main() {
    Solution s;
    s.addOperators("1234", -23);
    return 0;
}
