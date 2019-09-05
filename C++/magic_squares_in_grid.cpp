/*
 840. Magic Squares In Grid
 A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9
 such that each row, column, and both diagonals all have the same sum.

 Given an grid of integers, how many 3 x 3 "magic square" subgrids are there?
 (Each subgrid is contiguous).

 Example 1:

 Input:
 [
    [4,3,8,4],
    [9,5,1,9],
    [2,7,6,2]
 ]
 Output: 1
 Explanation:
 The following subgrid is a 3 x 3 magic square:
 438
 951
 276

 while this one is not:
 384
 519
 762

 In total, there is only one magic square inside the given grid.
 Note:

 1 <= grid.length <= 10
 1 <= grid[0].length <= 10
 0 <= grid[i][j] <= 15
*/
#include <iostream>
#include <sstream>
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
    int check(int x, int y, vector<vector<int>>& grid) {
        int sum = 0;
        vector<int> digit(10, 0);
        for (int i = x; i < x + 3; i++) {
            for (int j = y; j < y + 3; j++) {
                if (grid[i][j] < 1 or grid[i][j] > 9) {
                    return 0;
                }
                sum += grid[i][j];
                digit[grid[i][j]] += 1;
            }

            if (sum != 15) {
                return 0;
            }
            sum = 0;
        }

        for (int i = 1; i <= 9; ++i) {
            if (digit[i] != 1) {
                return 0;
            }
        }

        for (int j = y; j < y + 3; j++) {
            for (int i = x; i < x + 3; i++) {
                if (grid[i][j] < 1 || grid[i][j] > 9) {
                    return 0;
                }
                sum += grid[i][j];
            }

            if (sum != 15) {
                return 0;
            }
            sum = 0;
        }

        if (grid[x][y] + grid[x + 1][y + 1] + grid[x + 2][y + 2] != 15) {
            return 0;
        }
        if (grid[x][y + 2] + grid[x + 1][y + 1] + grid[x + 2][y] != 15) {
            return 0;
        }
        return 1;
    }
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m < 3) {
            return 0;
        }
        int n = grid[0].size();
        if (n < 3) {
            return 0;
        }

        int result = 0;
        for (int i = 0; i < m - 2; i++) {
            for (int j = 0; j < n - 2; j++) {
                result += check(i, j, grid);
            }
        }
        return result;
    }
};
