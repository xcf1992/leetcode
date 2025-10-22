/*
https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/description/
3195. Find the Minimum Area to Cover All Ones I

You are given a 2D binary array grid.
Find a rectangle with horizontal and vertical sides with the smallest area,
such that all the 1's in grid lie inside this rectangle.
Return the minimum possible area of the rectangle.



Example 1:

Input: grid = [[0,1,0],[1,0,1]]
Output: 6
Explanation:
The smallest rectangle has a height of 2 and a width of 3, so it has an area of 2 * 3 = 6.

Example 2:
Input: grid = [[1,0],[0,0]]
Output: 1
Explanation:
The smallest rectangle has both height and width 1, so its area is 1 * 1 = 1.

Constraints:
1 <= grid.length, grid[i].length <= 1000
grid[i][j] is either 0 or 1.
The input is generated such that there is at least one 1 in grid.
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

class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        size_t n = grid.size();
        size_t m = grid[0].size();
        size_t left = -1;
        size_t right = - 1;
        size_t top = -1;
        size_t bottom = -1;
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    if (left == -1 || left > j) {
                        left = j;
                    }

                    if (right == -1 || right < j) {
                        right = j;
                    }

                    if (top == -1 || top > i) {
                        top = i;
                    }

                    if (bottom == -1 || bottom < i) {
                        bottom = i;
                    }
                }
            }
        }

        return (right - left + 1) * (bottom - top + 1);
    }
};
