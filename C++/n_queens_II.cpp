/*
52. N-Queens II
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return the number of distinct solutions to the n-queens puzzle.

Example:

Input: 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown below.
[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    int totalNQueens(int n) {

    }
};

class Solution1 { // slow faster than 9.71%
    bool isValid(vector<int>& cur, int n) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (abs(i - j) == abs(cur[i] - cur[j])) {
                    return false;
                }
            }
        }
        return true;
    }
public:
    int totalNQueens(int n) {
        vector<int> cur(n, 0);
        iota(cur.begin(), cur.end(), 0);
        int result = 0;
        do {
            if (isValid(cur, n)) {
                result += 1;
            }
        } while (next_permutation(cur.begin(), cur.end()));
        return result;
    }
};
