/*
https://leetcode.com/problems/sudoku-solver/description/
37. Sudoku Solver

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
Empty cells are indicated by the character '.'.


A sudoku puzzle...


...and its solution numbers marked in red.

Note:

The given board contain only digits 1-9 and the character '.'.
You may assume that the given Sudoku puzzle will have a single unique solution.
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
#include <climits>
using namespace std;

class Solution {
private:
    bool isValid(int row, int col, vector<vector<char>>& board) {
        for (int i = 0; i != 9; i++) {
            if (i != col and board[row][col] == board[row][i]) {
                return false;
            }
        }

        for (int i = 0; i != 9; i++) {
            if (i != row and board[row][col] == board[i][col]) {
                return false;
            }
        }

        int sRow = (row / 3) * 3;
        int sCol = (col / 3) * 3;
        for (int i = 0; i != 3; i++) {
            for (int j = 0; j != 3; j++) {
                int x = sRow + i;
                int y = sCol + j;
                if (x != row and y != col and board[x][y] == board[row][col]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i != 9; i++) {
            for (int j = 0; j != 9; j++) {
                if (board[i][j] != '.') {
                    continue;
                }

                for (int k = 1; k <= 9; k++) {
                    board[i][j] = k + '0';
                    if (isValid(i, j, board) and solve(board)) {
                        return true;
                    }
                }
                board[i][j] = '.';
                return false;
            }
        }
        return true;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};