/*
 576. Out of Boundary Paths
 There is an m by n grid with a ball. Given the start coordinate (i,j) of the ball, you can move the ball to adjacent cell or cross the grid boundary in four directions (up, down, left, right). However, you can at most move N times. Find out the number of paths to move the ball out of grid boundary. The answer may be very large, return it after mod 109 + 7.
 
 Example 1:
 Input:m = 2, n = 2, N = 2, i = 0, j = 0
 Output: 6
 Explanation:
 
 Example 2:
 Input:m = 1, n = 3, N = 3, i = 0, j = 1
 Output: 12
 Explanation:
 
 Note:
 Once you move the ball out of boundary, you cannot move it back.
 The length and height of the grid is in range [1,50].
 N is in range [0,50].
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
private:
    int mod = 1e9 + 7;

    bool isValid(int m, int n, int r, int c) {
        return r >= 0 and c >= 0 and r < m and c < n;
    }
public:
    int findPaths(int m, int n, int N, int i, int j) {
        if (N == 0) {
            return 0;
        }
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(m, vector<int>(n, 0)));
        for (int y = 0; y < n; y++) {
            dp[0][0][y] += 1;
            dp[0][m - 1][y] += 1;
        }
        for (int x = 0; x < m; x++) {
            dp[0][x][0] += 1;
            dp[0][x][n - 1] += 1;
        }

        vector<int> rDiff({0, 0, -1, 1});
        vector<int> cDiff({1, -1, 0, 0});
        for (int k = 1; k < N; k++) {
            for (int r = 0; r < m; r++) {
                for (int c = 0; c < n; c++) {
                    for (int i = 0; i < 4; ++i) {
                        int nr = r + rDiff[i];
                        int nc = c + cDiff[i];
                        if (isValid(m, n, nr, nc)) {
                            dp[k][r][c] += dp[k - 1][nr][nc];
                            dp[k][r][c] %= mod;
                        }
                    }
                }
            }
        }

        int result = 0;
        for (int k = 0; k < N; k++) {
            result += dp[k][i][j];
            result %= mod;
        }
        return result;
    }
};

// BFS memory limit exceeded
class Solution1 {
private:
    int mod = 1e9 + 7;
public:
    int findPaths(int m, int n, int N, int i, int j) {
        int result = 0;
        queue<pair<int, int>> bfs;
        bfs.push(make_pair(i, j));
        
        int move = 0;
        while (move < N) {
            int count = bfs.size();
            for (int k = 0; k < count; k++) {
                pair<int, int> curPos = bfs.front();
                bfs.pop();
                
                int x = curPos.first - 1;
                int y = curPos.second;
                if (x < 0 || y < 0 || x >= m || y >= n) {
                    result += 1;
                }
                else {
                    bfs.push(make_pair(x, y));
                }
                
                x = curPos.first + 1;
                y = curPos.second;
                if (x < 0 || y < 0 || x >= m || y >= n) {
                    result += 1;
                }
                else {
                    bfs.push(make_pair(x, y));
                }
                
                x = curPos.first;
                y = curPos.second - 1;
                if (x < 0 || y < 0 || x >= m || y >= n) {
                    result += 1;
                }
                else {
                    bfs.push(make_pair(x, y));
                }
                
                x = curPos.first;
                y = curPos.second + 1;
                if (x < 0 || y < 0 || x >= m || y >= n) {
                    result += 1;
                }
                else {
                    bfs.push(make_pair(x, y));
                }
                result %= mod;
            }
            move += 1;
        }
        return result;
    }
};
