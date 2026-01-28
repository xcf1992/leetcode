/*
79. Word Search
https://leetcode.com/problems/word-search/

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell,
where "adjacent" cells are those horizontally or vertically neighboring.
The same letter cell may not be used more than once.

Example:
board =
[
['A','B','C','E'],
['S','F','C','S'],
['A','D','E','E']
]
Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
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
#include <set>
using namespace std;

class Solution {
private:
    vector<vector<char>> board;
    int row_cnt = 0;
    int col_cnt = 0;
    int rowOffsets[4] = {0, 1, 0, -1};
    int colOffsets[4] = {1, 0, -1, 0};

    bool search(int row, int col, const string& word, int index) {
        if (index >= word.size()) {
            return true;
        }

        if (row < 0 || row == row_cnt || col < 0 || col == col_cnt || board[row][col] != word[index]) {
            return false;
        }

        char temp = board[row][col];
        board[row][col] = '#';
        for (int d = 0; d < 4; ++d) {
            if (search(row + rowOffsets[d], col + colOffsets[d], word, index + 1)) {
                return true;
            }
        }
        board[row][col] = temp;
        return false;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        this->board = board;
        row_cnt = board.size();
        col_cnt = board[0].size();
        for (int i = 0; i < row_cnt; ++i) {
            for (int j = 0; j < col_cnt; ++j) {
                if (search(i, j, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};
