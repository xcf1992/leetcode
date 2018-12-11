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
    bool isValid(vector<vector<int>> board, int N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[0][0] ^ board[0][j] ^ board[i][0] ^ board[i][j] == 1) {
                    return false;
                }
            }
        }
        return true;
    }
public:
    int movesToChessboard(vector<vector<int>> board) {
        int N = board.size();
        if (!isValid(board, N)) {
            return -1;
        }
        
        
        return 0;
    }
};

int main() {
    Solution s;
    s.movesToChessboard({
        {0,1,0,1},
        {1,0,1,0},
        {0,1,1,0}
    });
    return 0;
}
