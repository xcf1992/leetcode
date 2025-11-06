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
using namespace std;

class Solution {
private:
    int calculate(int x, int y, vector<vector<int>>& grid) {
        int result = 0;

        if (x == 0 or grid[x - 1][y] == 0) {
            result += 1;
        }
        if (x == grid.size() - 1 or grid[x + 1][y] == 0) {
            result += 1;
        }

        if (y == 0 or grid[x][y - 1] == 0) {
            result += 1;
        }
        if (y == grid[0].size() - 1 or grid[x][y + 1] == 0) {
            result += 1;
        }

        return result;
    }

public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    perimeter += calculate(i, j, grid);
                }
            }
        }

        return perimeter;
    }
};

int main() {
    Solution s;
    return 0;
}