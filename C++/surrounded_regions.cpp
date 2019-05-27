/*
130. Surrounded Regions

Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:

X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
Explanation:

Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the board are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected horizontally or vertically.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;
    
    void dfs(vector<vector<char>>& board, int row, int col) {
        if (row < 0 or col < 0 or row >= m or col >= n) {
            return;
        }
        if (board[row][col] != 'O') {
            return;
        }
        
        board[row][col] = 'C';
        vector<int> rDiff = {1, -1, 0, 0};
        vector<int> cDiff = {0, 0, 1, -1};
        for (int i = 0; i < 4; ++i) {
            dfs(board, row + rDiff[i], col + cDiff[i]);
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        m = board.size();
        if (m == 0) {
            return;
        }
        n = board[0].size();
        
        for (int i = 0; i < m; ++i) {
            dfs(board, i, 0);
            dfs(board, i, n - 1);
        }
        for (int j = 0; j < n; ++j) {
            dfs(board, 0, j);
            dfs(board, m - 1, j);
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'C') {
                    board[i][j] = 'O';
                }
                else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
};