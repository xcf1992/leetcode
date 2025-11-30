/*
361. Bomb Enemy
https://leetcode.com/problems/bomb-enemy/

Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero),
return the maximum enemies you can kill using one bomb.

The bomb kills all the enemies in the same row and column from the planted point until it hits the wall
since the wall is too strong to be destroyed.

Note that you can only put the bomb at an empty cell.

Example:
For the given grid
0 E 0 0
E 0 W E
0 E 0 0
return 3. (Placing a bomb at (1,1) kills 3 enemies)
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
#include <climits>
#include <set>
using namespace std;

class Enemy {
public:
    int left;
    int right;
    int up;
    int down;

    Enemy() {
        left = 0;
        right = 0;
        up = 0;
        down = 0;
    }

    int sum() {
        return left + right + up + down;
    }
};

class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        int m = grid.size();
        if (m == 0) {
            return 0;
        }
        int n = grid[0].size();

        vector<vector<Enemy>> killedEnemy(m, vector<Enemy>(n, Enemy()));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != 'W') {
                    killedEnemy[i][j].up = (i == 0 ? 0 : killedEnemy[i - 1][j].up) + (grid[i][j] == 'E' ? 1 : 0);
                    killedEnemy[i][j].left = (j == 0 ? 0 : killedEnemy[i][j - 1].left) + (grid[i][j] == 'E' ? 1 : 0);
                }

                if (grid[m - i - 1][n - j - 1] != 'W') {
                    killedEnemy[m - i - 1][n - j - 1].down = (i == 0 ? 0 : killedEnemy[m - i][n - j - 1].down) +
                                                             (grid[m - i - 1][n - j - 1] == 'E' ? 1 : 0);
                    killedEnemy[m - i - 1][n - j - 1].right = (j == 0 ? 0 : killedEnemy[m - i - 1][n - j].right) +
                                                              (grid[m - i - 1][n - j - 1] == 'E' ? 1 : 0);
                }
            }
        }

        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                if (grid[i][j] == '0') {
                    result = max(result, killedEnemy[i][j].sum());
                }
        }
        return result;
    }
};