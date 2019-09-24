/*
22. Generate Parentheses

Given n pairs of parentheses,
write a function to generate all combinations of well-formed parentheses.
For example, given n = 3, a solution set is:
[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
private:
    void generate(vector<string>& result, string& parenthesis, int size, int left, int right) {
        if (parenthesis.size() == size * 2) {
            result.push_back(parenthesis);
            return;
        }

        if (left < size) {
            parenthesis += '(';
            generate(result, parenthesis, size, left + 1, right);
            parenthesis.pop_back();
        }
        if (left > right) {
            parenthesis += ')';
            generate(result, parenthesis, size, left, right + 1);
            parenthesis.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        if (n <= 0) {
            return {};
        }

        vector<string> result;
        string parenthesis = "";
        generate(result, parenthesis, n, 0, 0);
        return result;
    }
};
