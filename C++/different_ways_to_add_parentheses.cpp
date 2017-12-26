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
    vector<int> diffWaysToCompute(string input) {
        vector<int> results;

        for (int i = 0; i < input.size(); i++) {
            char c = input[i];
            if (ispunct(c)) {
                for (int a : diffWaysToCompute(input.substr(0, i))) {
                    for (int b : diffWaysToCompute(input.substr(i + 1))) {
                        if (c == '+') {
                            results.push_back(a + b);
                        } else if (c == '-') {
                            results.push_back(a - b);
                        } else if (c == '*') {
                            results.push_back(a * b);
                        }
                    }
                }
            }
        }

        if (results.empty()) {
            results.push_back(stoi(input));
        }
        return results;
    }
};

int main() {
    Solution s;
    return 0;
}