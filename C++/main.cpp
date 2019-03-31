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
    int M = 0;
    int N = 0;
    
    void change(int row, int col, vector<vector<int>>& A) {
        if (row < 0 or col < 0 or row >= M or col >= N) {
            return;
        }
        
        if (A[row][col] != 1) {
            return;
        }
        
        A[row][col] = 2;
        change(row + 1, col, A);
        change(row - 1, col, A);
        change(row, col + 1, A);
        change(row, col - 1, A);
    }
public:
    int numEnclaves(vector<vector<int>> A) {
        M = A.size();
        N = A[0].size();
        
        for (int row = 0; row < M ; ++row) {
            if (A[row][0] == 1) {
                change(row, 0, A);
            }
            if (A[row][0] == 1) {
                change(row, N - 1, A);
            }
        }
        for (int col = 0; col < N; ++col) {
            if (A[0][col] == 1) {
                change(0, col, A);
            }
            if (A[M - 1][col] == 1) {
                change(M - 1, col, A);
            }
        }
        
        int result = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                result += A[i][j] == 1 ? 1 : 0;
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    s.numEnclaves({{0,0,1,1,1,0,1,1,1,0,1},{1,1,1,1,0,1,0,1,1,0,0},{0,1,0,1,1,0,0,0,0,1,0},{1,0,1,1,1,1,1,0,0,0,1},{0,0,1,0,1,1,0,0,1,0,0},{1,0,0,1,1,1,0,0,0,1,1},{0,1,0,1,1,0,0,0,1,0,0},{0,1,1,0,1,0,1,1,1,0,0},{1,1,0,1,1,1,0,0,0,0,0},{1,0,1,1,0,0,0,1,0,0,1}});
    return 0;
}
