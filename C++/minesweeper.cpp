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
private:
    bool validClick(vector<vector<char>>& board, int x, int y) {
        return x >= 0 && y >= 0 && x < board.size() && y < board[0].size();
    }

    void visit(vector<vector<char>>& board, int x, int y) {
        if (!validClick(board, x, y)) {
            return;
        }

        if (board[x][y] == 'E') {
            int count = 0;
            if (validClick(board, x - 1, y - 1) && board[x- 1][y - 1] == 'M') {
                count += 1;
            }
            if (validClick(board, x - 1, y) && board[x - 1][y] == 'M') {
                count += 1;
            }
            if (validClick(board, x - 1, y + 1) && board[x - 1][y + 1] == 'M') {
                count += 1;
            }
            if (validClick(board, x, y - 1) && board[x][y - 1] == 'M') {
                count += 1;
            }
            if (validClick(board, x, y + 1) && board[x][y + 1] == 'M') {
                count += 1;
            }
            if (validClick(board, x + 1, y - 1) && board[x + 1][y - 1] == 'M') {
                count += 1;
            }
            if (validClick(board, x + 1, y) && board[x + 1][y] == 'M') {
                count += 1;
            }
            if (validClick(board, x + 1, y + 1) && board[x + 1][y + 1] == 'M') {
                count += 1;
            }

            if (count > 0) {
                board[x][y] = '0' + count;
            }
            else {
                board[x][y] = 'B';
                visit(board, x - 1, y - 1);
                visit(board, x - 1, y);
                visit(board, x - 1, y + 1);
                visit(board, x,y - 1);
                visit(board, x,y + 1);
                visit(board, x + 1, y - 1);
                visit(board, x + 1, y);
                visit(board, x + 1, y + 1);
            }
        }
    }

public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int x = click[0];
        int y = click[1];

        if (board[x][y] == 'M') {
            board[x][y] = 'X';
            return board;
        }

        visit(board, x, y);
        return board;
    }
};

int main() {
    Solution s;
    return 0;
}
