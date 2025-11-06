/*
 883. Projection Area of 3D Shapes
 On a N * N grid, we place some 1 * 1 * 1 cubes that are axis-aligned with the x, y, and z axes.

 Each value v = grid[i][j] represents a tower of v cubes placed on top of grid cell (i, j).

 Now we view the projection of these cubes onto the xy, yz, and zx planes.

 A projection is like a shadow, that maps our 3 dimensional figure to a 2 dimensional plane.

 Here, we are viewing the "shadow" when looking at the cubes from the top, the front, and the side.

 Return the total area of all three projections.

 Example 1:

 Input: [[2]]
 Output: 5
 Example 2:

 Input: [[1,2],[3,4]]
 Output: 17
 Explanation:
 Here are the three projections ("shadows") of the shape made with each axis-aligned plane.

 Example 3:

 Input: [[1,0],[0,2]]
 Output: 8
 Example 4:

 Input: [[1,1,1],[1,0,1],[1,1,1]]
 Output: 14
 Example 5:

 Input: [[2,2,2],[2,1,2],[2,2,2]]
 Output: 21


 Note:

 1 <= grid.length = grid[0].length <= 50
 0 <= grid[i][j] <= 50
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int res = 0;
        int n = grid.size();

        vector<int> rowMax(n, 0);
        vector<int> colMax(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                if (grid[i][j] > 0) {
                    res += 1;
                    rowMax[i] = max(rowMax[i], grid[i][j]);
                    colMax[j] = max(colMax[j], grid[i][j]);
                }
        }

        for (int i = 0; i < n; ++i) {
            res += rowMax[i];
            res += colMax[i];
        }
        return res;
    }
};

class Solution1 {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int res = 0;
        int n = grid.size();

        for (int i = 0; i < n; ++i) {
            int v = 0;
            for (int j = 0; j < n; ++j) {
                v = max(v, grid[i][j]);
            }
            res += v;
        }

        for (int j = 0; j < n; ++j) {
            int v = 0;
            for (int i = 0; i < n; ++i) {
                v = max(v, grid[i][j]);
            }
            res += v;
        }

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j])
                    res++;

        return res;
    }
};