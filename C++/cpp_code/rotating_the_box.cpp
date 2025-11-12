/*
https://leetcode.com/problems/rotating-the-box/description/
1861. Rotating the Box

You are given an m x n matrix of characters boxGrid representing a side-view of a box. Each cell of the box is one of
the following:

A stone '#'
A stationary obstacle '*'
Empty '.'
The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until
it lands on an obstacle, another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and
the inertia from the box's rotation does not affect the stones' horizontal positions.

It is guaranteed that each stone in boxGrid rests on an obstacle, another stone, or the bottom of the box.

Return an n x m matrix representing the box after the rotation described above.



Example 1:



Input: boxGrid = [["#",".","#"]]
Output: [["."],
         ["#"],
         ["#"]]
Example 2:



Input: boxGrid = [["#",".","*","."],
              ["#","#","*","."]]
Output: [["#","."],
         ["#","#"],
         ["*","*"],
         [".","."]]
Example 3:



Input: boxGrid = [["#","#","*",".","*","."],
              ["#","#","#","*",".","."],
              ["#","#","#",".","#","."]]
Output: [[".","#","#"],
         [".","#","#"],
         ["#","#","*"],
         ["#","*","."],
         ["#",".","*"],
         ["#",".","."]]


Constraints:

m == boxGrid.length
n == boxGrid[i].length
1 <= m, n <= 500
boxGrid[i][j] is either '#', '*', or '.'.
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
#include <map>
using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size();
        int n = boxGrid[0].size();
        vector<vector<char>> rotated_grid(n, vector<char>(m, '.'));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rotated_grid[j][m - 1 - i] = boxGrid[i][j];
            }
        }

        for (int col = 0; col < m; col++) {
            int bottom = n;
            for (int row = n - 1; row >= 0; row--) {
                if (rotated_grid[row][col] == '*') {
                    bottom = row;
                    continue;
                }

                if (rotated_grid[row][col] == '#') {
                    if (bottom - 1 != row) {
                        rotated_grid[bottom - 1][col] = '#';
                        rotated_grid[row][col] = '.';
                    }
                    bottom -= 1;
                }
            }
        }
        return rotated_grid;
    }
};