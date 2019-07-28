/*
1139. Largest 1-Bordered Square
Given a 2D grid of 0s and 1s,
return the number of elements in the largest square subgrid that has all 1s on its border,
or 0 if such a subgrid doesn't exist in the grid.

Example 1:

Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
Output: 9
Example 2:

Input: grid = [[1,1,0,0]]
Output: 1


Constraints:

1 <= grid.length <= 100
1 <= grid[0].length <= 100
grid[i][j] is 0 or 1
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

class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> row(m, vector<int>(n, 0));
        vector<vector<int>> col(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) {
                    row[i][j] = j > 0 ? 1 + row[i][j - 1] : 1;
                    col[i][j] = i > 0 ? 1 + col[i - 1][j] : 1;
                }
            }
        }

        int maxLen = 0;
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int len = min(row[i][j], col[i][j]);
                while (len > maxLen) {
                    if (row[i - len + 1][j] >= len and col[i][j - len + 1] >= len) {
                        maxLen = len;
                    }
                    len -= 1;
                }
            }
        }
        return maxLen * maxLen;
    }
};
