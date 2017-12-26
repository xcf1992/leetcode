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
    bool counted(int x, int y, vector<vector<char>>& board) {
        if (x != 0 && board[x - 1][y] == 'X') {
            return true;
        }

        if (y != 0 && board[x][y - 1] == 'X') {
            return true;
        }

        return false;
    }

public:
    int countBattleships(vector<vector<char>>& board) {
        int result = 0;

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == 'X' && !counted(i, j, board)) {
                    result += 1;
                }
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}