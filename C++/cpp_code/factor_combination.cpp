/*
254. Factor Combinations
https://leetcode.com/problems/factor-combinations/

Numbers can be regarded as product of its factors. For example,
8 = 2 x 2 x 2;
= 2 x 4.
Write a function that takes an integer n and return all possible combinations of its factors.

Note:
You may assume that n is always positive.
Factors should be greater than 1 and less than n.

Examples:
input: 1
output:
[]

input: 37
output:
[]

input: 12
output:
[
[2, 6],
[2, 2, 3],
[3, 4]
]

input: 32
output:
[
[2, 16],
[2, 2, 8],
[2, 2, 2, 4],
[2, 2, 2, 2, 2],
[2, 4, 4],
[4, 8]
]
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
#include <climits>
#include <map>
using namespace std;

class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        if (n <= 2) {
            return {};
        }

        vector<vector<int>> factors;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                int j = n / i;
                if (j >= i) {
                    factors.push_back({j, i});
                    for (vector<int> factor : getFactors(j)) {
                        if (i <= factor.back()) {
                            factor.push_back(i);
                            factors.push_back(factor);
                        }
                    }
                }
            }
        }
        return factors;
    }
};

class Solution1 {
private:
    vector<vector<int>> res;

public:
    vector<vector<int>> getFactors(int n) {
        vector<int> line;
        getFHelp(n, 2, line);
        return res;
    }

    void getFHelp(int n, int bottom, vector<int> line) {
        for (int i = bottom; i <= sqrt(n); i++) {
            if (n % i == 0) {
                vector<int> new_line = line;
                new_line.push_back(i);
                getFHelp(n / i, i, new_line);
                new_line.push_back(n / i);
                res.push_back(new_line);
            }
        }
    }
};