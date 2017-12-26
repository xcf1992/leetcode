#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

struct Position {
    int x;
    int y;
    Position(int x_, int y_) {
        x = x_;
        y = y_;
    }
};

void dfs(vector<vector<char>> &board, int x, int y) {
        int m = board.size();
        int n = board.front().size();
        
		cout << "x: " << x << " y: " << y << endl;

        if (y - 1 >= 0) {
            if (board[x][y - 1] == 'O') {
                board[x][y - 1] = 'N';
                dfs(board, x, y - 1);
            }
        }
        if (y + 1 < n) {
            if (board[x][y + 1] == 'O') {
                board[x][y + 1] = 'N';
                dfs(board, x, y + 1);
            }
        }
        if (x - 1 >= 0) {
            if (board[x - 1][y] == 'O') {
                board[x - 1][y] = 'N';
                dfs(board, x - 1, y);
            }
        }
        if (x + 1 < m) {
            if (board[x + 1][y] == 'O') {
                board[x + 1][y] = 'N';
                dfs(board, x + 1, y);
            }
        }
        
        return;
    }

void solve(vector<vector<char>> &board) {
         if (board.empty()) {
            return;
        }
        
        int m = board.size();
        int n = board.front().size();
        
        queue<struct Position> que;
        
        for (int j = 0; j != n; j++) {
            if (board[0][j] == 'O') {
                board[0][j] == 'N';
                struct Position pos(0, j);
                que.push(pos);
            }
            if (board[m - 1][j] == 'O') {
                board[m - 1][j] == 'N';
                struct Position pos(m - 1, j);
                que.push(pos);
            }
        }
        for (int i = 1; i <= m - 2; i++) {
            if (board[i][0] == 'O') {
                board[i][0] = 'N';
                struct Position pos(i, 0);
                que.push(pos);
            }
            if (board[i][n - 1] == 'O') {
                board[i][n - 1] = 'N';
                struct Position pos(i, n - 1);
                que.push(pos);
            }
        }
        
        while (!que.empty()) {
            struct Position pos = que.front();
            que.pop();
            int i = pos.x;
            int j = pos.y;
            
            if (i - 1 >= 0 && board[i - 1][j] == 'O') {
                board[i - 1][j] = 'N';
                struct Position pos(i - 1, j);
                que.push(pos);
            }
            if (i + 1 < m && board[i + 1][j] == 'O') {
                board[i + 1][j] = 'N';
                struct Position pos(i + 1, j);
                que.push(pos);
            }
            if (j - 1 >= 0 && board[i][j - 1] == 'O') {
                board[i][j - 1] = 'N';
                struct Position pos(i, j - 1);
                que.push(pos);
            }
            if (j + 1 < n && board[i][j + 1] == 'O') {
                board[i][j + 1] = 'N';
                struct Position pos(i, j + 1);
                que.push(pos);
            }
        }
        
        for (int i = 0; i != m; i++) {
            for (int j = 0; j != n; j++) {
                if (board[i][j] == 'N') {
                    board[i][j] = 'O';
                }
                else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
        
        return;
    }
    
int main() {
	vector<vector<char>> board;
	vector<char> fuck;
	fuck.push_back('O');
	/*vector<char> row;
	row.push_back('X');
	row.push_back('O');
	row.push_back('X');
	row.push_back('O');
	row.push_back('X');
	row.push_back('O');

	vector<char> row1;
	row1.push_back('O');
	row1.push_back('X');
	row1.push_back('O');
	row1.push_back('X');
	row1.push_back('O');
	row1.push_back('X');

	vector<char> row2 = row;
	vector<char> row3 = row1;
	board.push_back(row);
	board.push_back(row1);
	board.push_back(row2);
	board.push_back(row3);*/
	board.push_back(row);
	solve(board);
	return 0;
}