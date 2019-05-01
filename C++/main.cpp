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
    long parseNum(string& s, int& i) {
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
            if (s[i] == ' ') {
                continue;
            }

            long n = s[i] == '(' ? parseExp(s, ++i) : parseNum(s, i);
            if (op == '+') {
                nums.push_back(n);
            }
            else if (op == '-') {
                nums.push_back(-n);
            }
            else if (op == '*') {
                nums.back() *= n;
            }
            else if (op == '/') {
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

int main() {
    Solution s;
    s.calculate("- 3 + 2 - ( - 3 )");
    return 0;
}
