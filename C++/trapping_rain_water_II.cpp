/*
407. Trapping Rain Water II
Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map,
compute the volume of water it is able to trap after raining.

Note:

Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.
Example:

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

Return 4.


The above image represents the elevation map [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]] before the rain.

After the rain, water is trapped between the blocks. The total volume of water trapped is 4.
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
using namespace std;

/*
It takes me a long time to figure it out, but actually the idea is quite straightforward. Imagine the pool is surrounded by many bars. The water can only go out from the lowest bar. So we always start from the lowest boundary and keep pushing the bar from boundary towards inside. It works as if we are replacing the old bars with a bar higher than it.
See the following simple example:
4 4 4 4
4 0 1 2
4 4 4 4
it looks like we push the bar of 2 towards left and record the difference. Then you can use the same procedure with the following figure
4 4 4 4
4 0 2 2
4 4 4 4

cause we use priority_queue, so we make sure we always move the bounary with lowest height first
*/
struct myComp {
    bool operator()(pair<int, int>& a, pair<int, int>& b) {
        return a.first > b.first;
    }
};
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int row = heightMap.size();
        if (row == 0) {
            return 0;
        }
        int col = heightMap[0].size();

        priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> que;
        vector<vector<int>> visited(row, vector<int>(col, 0));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (i == 0 or i == row - 1 or j == 0 or j == col - 1) {
                    que.push({heightMap[i][j], i * col + j});
                    visited[i][j] = 1;
                }
            }
        }

        int ans = 0;
        int curMax = INT_MIN;
        vector<vector<int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while(!que.empty()) {
            int height = que.top().first;
            int x = que.top().second / col;
            int y = que.top().second % col;
            que.pop();

            curMax = max(curMax, height);
            for (auto d: dir) {
                int x2 = x + d[0];
                int y2 = y + d[1];
                if (x2 >= row or x2 < 0 or y2 < 0 or y2 >= col or visited[x2][y2]) {
                    continue;
                }

                visited[x2][y2] = 1;
                if (heightMap[x2][y2] < curMax) {
                    ans += curMax - heightMap[x2][y2];
                }
                que.push({max(curMax, heightMap[x2][y2]), x2 * col + y2});
            }
        }
        return ans;
    }
};

class Solution1 {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = n;
        if (m < 3) {
            return 0;
        }
        int n = heightMap[0].size();
        if (n < 3) {
            return 0;
        }
        vector<vector<int>> left(m, vector<int>(n, 0));
        vector<vector<int>> right(m, vector<int>(n, 0));
        vector<vector<int>> up(m, vector<int>(n, 0));
        vector<vector<int>> down(m, vector<int>(n, 0));

        for (int i = 1; i < m; i++) {
            left[i][0] = heightMap[i][0];
            right[i][n - 1] = heightMap[i][n - 1];
            for (int j = 1; j < n; j++) {
                left[i][j] = max(left[i][j - 1], heightMap[i][j]);
                right[i][n - j - 1] = max(right[i][n - j], heightMap[i][n - j - 1]);
            }
        }

        for (int j = 1; j < n; j++) {
            up[0][j] = heightMap[0][j];
            down[m - 1][j] = heightMap[m - 1][j];
            for (int i = 1; i < m; i++) {
                up[i][j] = max(up[i - 1][j], heightMap[i][j]);
                down[m - i - 1][j] = max(down[m - i][j], heightMap[m - i - 1][j]);
            }
        }

        int result = 0;
        vector<vector<int>> waterMap(m, vector<int>(n, 0));
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                int wall = min(min(left[i][j], right[i][j]), min(up[i][j], down[i][j]));
                if (wall > heightMap[i][j]) {
                    result += wall - heightMap[i][j];
                    waterMap[i][j] = wall - heightMap[i][j];
                }
            }
        }

        bool spilled = true;
        vector<int> rowOffset({-1,1,0,0});
        vector<int> colOffset({0,0,1,-1});
        while (spilled) {
            spilled = false;

            for (int i = 1; i < m - 1; i++) {
                for (int j = 1; j < n - 1; j++) {
                    if (waterMap[i][j] != 0) {
                        for (int move = 0; move < 4; move++) {
                            int row = i + rowOffset[move];
                            int col = j + colOffset[move];
                            int curWater = waterMap[i][j] + heightMap[i][j];
                            int neighbor = waterMap[row][col] + heightMap[row][col];
                            if (curWater > neighbor) {
                                spilled = true;
                                int spillWater = curWater - max(neighbor, heightMap[i][j]);
                                waterMap[i][j] = waterMap[i][j] - spillWater;
                                result -= spillWater;
                            }
                        }
                    }
                }
            }
        }
        return result;
    }
};

