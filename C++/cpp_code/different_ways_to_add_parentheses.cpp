/*
241. Different Ways to Add Parentheses
https://leetcode.com/problems/different-ways-to-add-parentheses/

Given a string of numbers and operators,
return all possible result from computing all the different possible ways to group numbers and operators.
The valid operators are +, - and *.

Example 1:
Input: "2-1-1"
Output: [0, 2]
Explanation:
((2-1)-1) = 0
(2-(1-1)) = 2

Example 2:
Input: "2*3-4*5"
Output: [-34, -14, -10, -10, 10]
Explanation:
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
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
using namespace std;

class Solution {
private:
    unordered_map<string, vector<int>> memo;

public:
    vector<int> diffWaysToCompute(string input) {
        if (memo.find(input) != memo.end()) {
            return memo[input];
        }

        vector<int> result;
        for (int i = 0; i < input.size(); i++) {
            char c = input[i];
            if (isdigit(c)) {
                continue;
            }

            for (int a : diffWaysToCompute(input.substr(0, i))) {
                for (int b : diffWaysToCompute(input.substr(i + 1))) {
                    if (c == '+') {
                        result.push_back(a + b);
                    } else if (c == '-') {
                        result.push_back(a - b);
                    } else if (c == '*') {
                        result.push_back(a * b);
                    }
                }
            }
        }

        if (result.empty()) {
            result.push_back(stoi(input));
        }
        memo[input] = result;
        return result;
    }
};