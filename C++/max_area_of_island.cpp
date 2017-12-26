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
    void check(int x, int y, int& temp, int& result, vector<vector<int>>& grid, vector<vector<bool>>& visit) {
        int m = grid.size();
        int n = grid[0].size();
        if (x >= 0 && x < m && y >= 0 && y < n && !visit[x][y] && grid[x][y] == 1) {
            visit[x][y] = true;
            temp += 1;

            check(x, y + 1, temp, result, grid, visit);
            check(x, y - 1, temp, result, grid, visit);
            check(x + 1, y, temp, result, grid, visit);
            check(x - 1, y, temp, result, grid, visit);
        }
        result = max(result, temp);
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int result = 0;
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visit(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!visit[i][j] && grid[i][j] == 1) {
                    int temp = 0;
                    check(i, j, temp, result, grid, visit);
                }
            }
        }
        return result;
    }
};