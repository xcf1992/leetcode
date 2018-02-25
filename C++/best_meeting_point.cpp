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

/*
A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

For example, given three people living at (0,0), (0,4), and (2,2):

1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
The point (0,2) is an ideal meeting point, as the total travel distance of 2+2+2=6 is minimal. So return 6.
*/
class Solution {
private:
    int calculate(vector<int>& position) {
        int result = 0;

        int middle = position[position.size() / 2];
        for (int i = 0; i < position.size(); i++) {
            result += abs(position[i] - middle);
        }

        return result;
    }
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        vector<int> row;
        vector<int> col;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    row.push_back(i);
                    col.push_back(j);
                }
            }
        }

        sort(col.begin(), col.end());

        return calculate(row) + calculate(col);
    }
};