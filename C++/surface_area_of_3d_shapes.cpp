/*
 892. Surface Area of 3D Shapes
 On a N * N grid, we place some 1 * 1 * 1 cubes.

 Each value v = grid[i][j] represents a tower of v cubes placed on top of grid cell (i, j).

 Return the total surface area of the resulting shapes.

 Example 1:

 Input: [[2]]
 Output: 10
 Example 2:

 Input: [[1,2],[3,4]]
 Output: 34
 Example 3:

 Input: [[1,0],[0,2]]
 Output: 16
 Example 4:

 Input: [[1,1,1],[1,0,1],[1,1,1]]
 Output: 32
 Example 5:

 Input: [[2,2,2],[2,1,2],[2,2,2]]
 Output: 46


 Note:

 1 <= N <= 50
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
    int surfaceArea(vector<vector<int>>& grid) {
        int result = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] != 0) {
                    result += 2;
                }

                int left = j - 1 >= 0 ? grid[i][j - 1] : 0;
                result += max(0, grid[i][j] - left);

                int right = j + 1 < grid[i].size() ? grid[i][j + 1] : 0;
                result += max(0, grid[i][j] - right);

                int up = i - 1 >= 0 ? grid[i - 1][j] : 0;
                result += max(0, grid[i][j] - up);

                int down = i + 1 < grid.size() ? grid[i + 1][j] : 0;
                result += max(0, grid[i][j] - up);
            }
        }
        return result;
    }
};
