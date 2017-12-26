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
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                count = 0;
                for (int x = max(i - 1, 0); x < min(i + 2, m); x++) {
                    for (int y = max(j - 1, 0); y < min(j + 2, n); y++) {
                        count += board[x][y] & 1;
                    }
                }

                if (count == 3 || count - board[i][j] == 3) {
                    board[i][j] |= 2;
                }
            }
        }


        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] >>= 1;
            }
        }
    }
};

int main() {
    Solution s;
    return 0;
}