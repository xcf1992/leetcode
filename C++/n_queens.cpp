/*
51. N-Queens
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

Example:

Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
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
private:
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

    vector<string> draw(vector<int>& cur, int n) {
        vector<string> graph;
        for (int c : cur) {
            string row = string(n, '.');
            row[c] = 'Q';
            graph.push_back(row);
        }
        return graph;
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<int> cur(n, 0);
        iota(cur.begin(), cur.end(), 0);
        vector<vector<string>> result;
        do {
            if (isValid(cur, n)) {
                result.push_back(draw(cur, n));
            }
        } while (next_permutation(cur.begin(), cur.end()));
        return result;
    }
};

class Solution1 {
private:
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

    vector<string> draw(vector<int>& cur, int n) {
        vector<string> graph;
        for (int c : cur) {
            string row = string(n, '.');
            row[c] = 'Q';
            graph.push_back(row);
        }
        return graph;
    }

    void dfs(vector<vector<string>>& result, vector<int>& cur, int level, int n) {
        if (level == n) {
            if (!isValid(cur, n)) {
                return;
            }
            result.push_back(draw(cur, n));
            return;
        }

        for (int i = level; i < n; ++i) {
            swap(cur[i], cur[level]);
            dfs(result, cur, level + 1, n);
            swap(cur[i], cur[level]);
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<int> cur;
        for (int i = 0; i < n; ++i) {
            cur.push_back(i);
        }
        dfs(result, cur, 0, n);
        return result;
    }
};
