/*
118. Pascal's Triangle
Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
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
#include <stdio.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows == 0) {
            return {};
        }

        vector<vector<int>> result;
        result.push_back({1});
        for (int i = 1; i < numRows; ++i) {
            vector<int> cur;
            cur.push_back(1);
            for (int j = 1; j < result[i - 1].size(); ++j) {
                cur.push_back(result[i - 1][j - 1] + result[i - 1][j]);
            }
            cur.push_back(1);
            result.push_back(cur);
        }
        return result;
    }
};
