/*
36. Valid Sudoku
Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.

A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

Example 1:

Input:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: true
Example 2:

Input:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being
    modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.
The given board contain only digits 1-9 and the character '.'.
The given board size is always 9x9.
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
    int n = 0;

    bool isValid(vector<char> values) {
        vector<int> checked(9, 0);
        for (int i = 0; i != n; ++i) {
            if (values[i] == '.') {
                continue;
            }
            if (checked[values[i] - '1']) {
                return false;
            }
            checked[values[i] - '1'] = 1;
        }
        return true;
    }

    bool checkRows(vector<vector<char>>& board) {
        for (int i = 0; i != n; i++) {
            if (!isValid(board[i])) {
                return false;
            }
        }
        return true;
    }

    bool checkColumns(vector<vector<char>>& board) {
        for (int j = 0; j < n; ++j) {
            vector<char> values;
            for (int i = 0; i < n; ++i) {
                values.push_back(board[i][j]);
            }
            if (!isValid(values)) {
                return false;
            }
        }
        return true;
    }

    bool checkSubboxes(vector<vector<char>>& board) {
        for (int i = 0; i < n; i += 3) {
            for (int j = 0; j < n; j += 3) {
                vector<char> values;
                for (int row = 0; row < 3; ++row) {
                    for (int col = 0; col < 3; ++col) {
                        values.push_back(board[i + row][j + col]);
                    }
                }
                if (!isValid(values)) {
                    return false;
                }
            }
        }
        return true;
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        n = board.size();
        return checkRows(board) and checkColumns(board) and checkSubboxes(board);
    }
};
