/*
 827. Making A Large Island
 In a 2D grid of 0s and 1s, we change at most one 0 to a 1.

 After, what is the size of the largest island? (An island is a 4-directionally connected group of 1s).

 Example 1:

 Input: [[1, 0], [0, 1]]
 Output: 3
 Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
 Example 2:

 Input: [[1, 1], [1, 0]]
 Output: 4
 Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
 Example 3:

 Input: [[1, 1], [1, 1]]
 Output: 4
 Explanation: Can't change any 0 to 1, only one island with area = 4.


 Notes:

 1 <= grid.length = grid[0].length <= 50.
 0 <= grid[i][j] <= 1.
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
#include <numeric>
using namespace std;

// so we first calculate the size of each single island
// then for each point with value == 0, we we check the sum of island area around it
class Solution {
private:
    vector<int> dr = {-1, 0, 1, 0};
    vector<int> dc = {0, -1, 0, 1};
    int N = 0;

    int getArea(vector<vector<int>>& grid, int r, int c, int index) {
        int area = 1;
        grid[r][c] = index;
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 or nc < 0 or nr >= N or nc >= N) {
                continue;
            }
            if (grid[nr][nc] == 1) {
                grid[nr][nc] = index;
                area += getArea(grid, nr, nc, index);
            }
        }
        return area;
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        N = grid.size();
        if (N == 0) {
            return 0;
        }

        vector<int> area(N * N + 2, 0);
        int index = 2;
        int result = 0;
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (grid[r][c] == 1) {
                    area[index] = getArea(grid, r, c, index);
                    result = max(result, area[index]); // in case all grids are 1, then below code will node be used, and the result will be grid area
                    index += 1;
                }
            }
        }

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (grid[r][c] == 0) {
                    unordered_set<int> visited;
                    for (int i = 0; i < 4; i++) {
                        int nr = r + dr[i];
                        int nc = c + dc[i];
                        if (nr < 0 or nc < 0 or nr >= N or nc >= N) {
                            continue;
                        }
                        if (grid[nr][nc] > 1) {
                            visited.insert(grid[nr][nc]);
                        }
                    }
                    int temp = 1;
                    for (int i : visited) {
                        temp += area[i];
                    }
                    result = max(result, temp);
                }
            }
        }
        return result;
    }
};
