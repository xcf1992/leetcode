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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;
    vector<int> diff = {0, 1, 0, -1, 0};
    void dfs(int row, int col, vector<vector<int>>& grid) {
        if (row < 0 or col < 0 or row >= m or col >= n or grid[row][col] == 1) {
            return;
        }

        grid[row][col] = 1;
        for (int i = 1; i < diff.size(); ++i) {
            dfs(row + diff[i], col + diff[i - 1], grid);
        }
    }
public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) {
            return 0;
        }
        int n = grid[0].size();

        for (int i = 0; i < m; ++i) {
            dfs(i, 0, grid);
            dfs(i, n - 1, grid);
        }
        for (int j = 0; j < n; ++j) {
            dfs(0, j, grid);
            dfs(m - 1, j, grid);
        }

        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    result += 1;
                    dfs(i, j, grid);
                }
            }
        }
        return result;
    }
};

int main() {
    vector<vector<int>> matrix({{1,1,1,1,1,1,1,0},{1,0,0,0,0,1,1,0},{1,0,1,0,1,1,1,0},{1,0,0,0,0,1,0,1},{1,1,1,1,1,1,1,0}});
    
    Solution s;
    s.closedIsland(matrix);
}
