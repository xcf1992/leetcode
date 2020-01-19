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
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        queue<vector<int>> bfs;
        bfs.push({0, 0, 0});
        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(k + 1, false)));
        visited[0][0][0] = true;

        vector<int> diff({0, 1, 0, -1, 0});
        int result = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; ++i) {
                int row = bfs.front()[0];
                int col = bfs.front()[1];
                int curK = bfs.front()[2];
                bfs.pop();

                if (row == m - 1 and col == n - 1) {
                    return result;
                }

                for (int k = 1; k < diff.size(); ++k) {
                    int nexR = row + diff[k];
                    int nexC = col + diff[k - 1];
                    int nexK = curK;
                    if (nexR >= 0 and nexC >= 0 and nexR < m and nexC < n) {
                        if (grid[nexR][nexC] == 1) {
                            nexK += 1;
                        }
                        if (nexK <= k and !visited[nexR][nexC][nexK]) {
                            visited[nexR][nexC][nexK] = true;
                            bfs.push({nexR, nexC, nexK});
                        }
                    }
                }
            }
            result += 1;
        }
        return -1;
    }
};

int main() {
    vector<vector<int>> matrix({{0,1,1,0,0},{1,1,0,1,0}});
    
    Solution s;
    s.shortestPath(matrix, 7);
}
