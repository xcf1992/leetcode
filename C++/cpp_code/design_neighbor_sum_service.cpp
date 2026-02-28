/*
https://leetcode.com/problems/design-neighbor-sum-service/description/
3242. Design Neighbor Sum Service

You are given a n x n 2D array grid containing distinct elements in the range [0, n2 - 1].

Implement the NeighborSum class:

NeighborSum(int [][]grid) initializes the object.
int adjacentSum(int value) returns the sum of elements which are adjacent neighbors of value, that is either to the top,
left, right, or bottom of value in grid. int diagonalSum(int value) returns the sum of elements which are diagonal
neighbors of value, that is either to the top-left, top-right, bottom-left, or bottom-right of value in grid.




Example 1:

Input:

["NeighborSum", "adjacentSum", "adjacentSum", "diagonalSum", "diagonalSum"]

[[[[0, 1, 2], [3, 4, 5], [6, 7, 8]]], [1], [4], [4], [8]]

Output: [null, 6, 16, 16, 4]

Explanation:



The adjacent neighbors of 1 are 0, 2, and 4.
The adjacent neighbors of 4 are 1, 3, 5, and 7.
The diagonal neighbors of 4 are 0, 2, 6, and 8.
The diagonal neighbor of 8 is 4.
Example 2:

Input:

["NeighborSum", "adjacentSum", "diagonalSum"]

[[[[1, 2, 0, 3], [4, 7, 15, 6], [8, 9, 10, 11], [12, 13, 14, 5]]], [15], [9]]

Output: [null, 23, 45]

Explanation:



The adjacent neighbors of 15 are 0, 10, 7, and 6.
The diagonal neighbors of 9 are 4, 12, 14, and 15.


Constraints:

3 <= n == grid.length == grid[0].length <= 10
0 <= grid[i][j] <= n2 - 1
All grid[i][j] are distinct.
value in adjacentSum and diagonalSum will be in the range [0, n2 - 1].
At most 2 * n2 calls will be made to adjacentSum and diagonalSum.
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
#include <map>
using namespace std;

class NeighborSum {
private:
    int n_ = 0;
    vector<int> val_to_idx_;
    vector<vector<int>> grid_;

    bool is_valid(int row, int col) {
        return row >= 0 && row < n_ && col >= 0 && col < n_;
    }

public:
    NeighborSum(vector<vector<int>>& grid) {
        n_ = grid.size();
        val_to_idx_.resize(n_ * n_, -1);
        for (int i = 0; i < n_; i++) {
            for (int j = 0; j < n_; j++) {
                val_to_idx_[grid[i][j]] = i * n_ + j;
            }
        }
        grid_ = grid;
    }

    int adjacentSum(int value) {
        int cur_idx = val_to_idx_[value];
        int cur_row = cur_idx / n_;
        int cur_col = cur_idx % n_;
        int rst = 0;
        vector<int> diff({0, 1, 0, -1, 0});
        for (int i = 0; i < 4; i++) {
            int next_row = cur_row + diff[i];
            int next_col = cur_col + diff[i + 1];
            if (is_valid(next_row, next_col)) {
                rst += grid_[next_row][next_col];
            }
        }
        return rst;
    }

    int diagonalSum(int value) {
        int cur_idx = val_to_idx_[value];
        int cur_row = cur_idx / n_;
        int cur_col = cur_idx % n_;
        int rst = 0;
        vector<int> diff({-1, 1, 1, -1, -1});
        for (int i = 0; i < 4; i++) {
            int next_row = cur_row + diff[i];
            int next_col = cur_col + diff[i + 1];
            if (is_valid(next_row, next_col)) {
                rst += grid_[next_row][next_col];
            }
        }
        return rst;
    }
};

/**
 * Your NeighborSum object will be instantiated and called as such:
 * NeighborSum* obj = new NeighborSum(grid);
 * int param_1 = obj->adjacentSum(value);
 * int param_2 = obj->diagonalSum(value);
 */