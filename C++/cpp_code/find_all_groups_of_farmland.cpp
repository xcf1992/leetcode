/*
https://leetcode.com/problems/find-all-groups-of-farmland/description/
1992. Find All Groups of Farmland

You are given a 0-indexed m x n binary matrix land where a 0 represents a hectare of forested land and a 1 represents a
hectare of farmland.

To keep the land organized, there are designated rectangular areas of hectares that consist entirely of farmland. These
rectangular areas are called groups. No two groups are adjacent, meaning farmland in one group is not four-directionally
adjacent to another farmland in a different group.

land can be represented by a coordinate system where the top left corner of land is (0, 0) and the bottom right corner
of land is (m-1, n-1). Find the coordinates of the top left and bottom right corner of each group of farmland. A group
of farmland with a top left corner at (r1, c1) and a bottom right corner at (r2, c2) is represented by the 4-length
array [r1, c1, r2, c2].

Return a 2D array containing the 4-length arrays described above for each group of farmland in land. If there are no
groups of farmland, return an empty array. You may return the answer in any order.



Example 1:


Input: land = [[1,0,0],[0,1,1],[0,1,1]]
Output: [[0,0,0,0],[1,1,2,2]]
Explanation:
The first group has a top left corner at land[0][0] and a bottom right corner at land[0][0].
The second group has a top left corner at land[1][1] and a bottom right corner at land[2][2].
Example 2:


Input: land = [[1,1],[1,1]]
Output: [[0,0,1,1]]
Explanation:
The first group has a top left corner at land[0][0] and a bottom right corner at land[1][1].
Example 3:


Input: land = [[0]]
Output: []
Explanation:
There are no groups of farmland.


Constraints:

m == land.length
n == land[i].length
1 <= m, n <= 300
land consists of only 0's and 1's.
Groups of farmland are rectangular in shape.
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
#include <climits>
#include <set>
using namespace std;

class Solution {
private:
    vector<int> diff = {0, 1, 0, -1, 0};
    int m_ = 0;
    int n_ = 0;

    void dfs(vector<vector<int>>& land, int row, int col, int& end_row, int& end_col) {
        if (row < 0 || col < 0 || row >= m_ || col >= n_) {
            return;
        }

        if (land[row][col] != 1) {
            return;
        }

        if (row >= end_row && col >= end_col) {
            end_row = row;
            end_col = col;
        }

        land[row][col] = 0;
        for (int i = 0; i < 4; i++) {
            int next_row = row + diff[i];
            int next_col = col + diff[i + 1];
            dfs(land, next_row, next_col, end_row, end_col);
        }
    }
public:
    vector<vector<int>> findFarmland(vector<vector<int>>& land) {
        m_ = land.size();
        n_ = land[0].size();
        vector<vector<int>> rst;
        for (int i = 0; i < m_; i++) {
            for (int j = 0; j < n_; j++) {
                if (land[i][j] != 1) {
                    continue;
                }

                int end_row = i;
                int end_col = j;
                dfs(land, i, j, end_row, end_col);
                rst.push_back({i, j, end_row, end_col});
            }
        }
        return rst;
    }
};