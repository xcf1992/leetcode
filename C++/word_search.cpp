/*
 79. Word Search
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

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
#include <stdio.h>
#include <map>
#include <set>
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;
    bool find(vector<vector<char>>& board, int index, int row, int col, string& word, vector<vector<bool>>& visited) {
        if (index >= word.size()) {
            return true;
        }
        if (row < 0 or col < 0 or row >= m or col >= n or visited[row][col] or word[index] != board[row][col]) {
            return false;
        }

        visited[row][col] = true;
        vector<int> rDiff({0, 0, 1, -1});
        vector<int> cDiff({1, -1, 0, 0});
        for (int i = 0; i < 4; ++i) {
            int r = row + rDiff[i];
            int c = col + cDiff[i];
            if (find(board, index + 1, r, c, word, visited)) {
                return true;
            }
        }
        visited[row][col] = false;
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (word.empty()) {
            return true;
        }

        m = board.size();
        if (m == 0) {
            return false;
        }
        n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (find(board, 0, i, j, word, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
};
