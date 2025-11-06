/*
https://leetcode.com/problems/last-day-where-you-can-still-cross/
1970. Last Day Where You Can Still Cross
There is a 1-based binary matrix where 0 represents land and 1 represents water. You are given integers row and col
representing the number of rows and columns in the matrix, respectively.

Initially on day 0, the entire matrix is land. However, each day a new cell becomes flooded with water. You are given a
1-based 2D array cells, where cells[i] = [ri, ci] represents that on the ith day, the cell on the rith row and cith
column (1-based coordinates) will be covered with water (i.e., changed to 1).

You want to find the last day that it is possible to walk from the top to the bottom by only walking on land cells. You
can start from any cell in the top row and end at any cell in the bottom row. You can only travel in the four cardinal
directions (left, right, up, and down).

Return the last day where it is possible to walk from the top to the bottom by only walking on land cells.



Example 1:


Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
Output: 2
Explanation: The above image depicts how the matrix changes each day starting from day 0.
The last day where it is possible to cross from top to bottom is on day 2.
Example 2:


Input: row = 2, col = 2, cells = [[1,1],[1,2],[2,1],[2,2]]
Output: 1
Explanation: The above image depicts how the matrix changes each day starting from day 0.
The last day where it is possible to cross from top to bottom is on day 1.
Example 3:


Input: row = 3, col = 3, cells = [[1,2],[2,1],[3,3],[2,2],[1,1],[1,3],[2,3],[3,2],[3,1]]
Output: 3
Explanation: The above image depicts how the matrix changes each day starting from day 0.
The last day where it is possible to cross from top to bottom is on day 3.


Constraints:

2 <= row, col <= 2 * 104
4 <= row * col <= 2 * 104
cells.length == row * col
1 <= ri <= row
1 <= ci <= col
All the values of cells are unique.
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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int left = 1;
        int right = cells.size();
        int result = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (can_cross(cells, row, col, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return result;
    }

private:
    vector<int> dir = {0, 1, 0, -1, 0};

    bool can_cross(vector<vector<int>>& cells, int row, int col, int day) {
        vector<vector<int>> grid(row, vector<int>(col, 0));
        for (int i = 0; i < day; ++i) {
            grid[cells[i][0] - 1][cells[i][1] - 1] = 1;
        }

        queue<pair<int, int>> bfs;
        for (int j = 0; j < col; ++j) {
            if (grid[0][j] == 0) {
                bfs.push(make_pair(0, j));
                grid[0][j] = 1;
            }
        }

        while (!bfs.empty()) {
            int cur_r = bfs.front().first;
            int cur_c = bfs.front().second;
            bfs.pop();

            if (cur_r == row - 1) {
                return true;
            }

            for (int i = 0; i < 4; i++) {
                int next_r = cur_r + dir[i];
                int next_c = cur_c + dir[i + 1];
                if (next_r < 0 || next_r >= row || next_c < 0 || next_c >= col || grid[next_r][next_c] == 1) {
                    continue;
                }

                grid[next_r][next_c] = 1;
                bfs.push(make_pair(next_r, next_c));
            }
        }
        return false;
    }
};