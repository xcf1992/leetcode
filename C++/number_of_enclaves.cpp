/*
 1031. Number of Enclaves
 Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)

 A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.

 Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves.



 Example 1:

 Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
 Output: 3
 Explanation:
 There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.
 Example 2:

 Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
 Output: 0
 Explanation:
 All 1s are either on the boundary or can reach the boundary.


 Note:

 1 <= A.length <= 500
 1 <= A[i].length <= 500
 0 <= A[i][j] <= 1
 All rows have the same size.
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
    int numEnclaves(vector<vector<int>>& A) {
        M = A.size();
        N = A[0].size();

        for (int row = 0; row < M ; ++row) {
            if (A[row][0] == 1) {
                change(row, 0, A);
            }
            if (A[row][N - 1] == 1) {
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
