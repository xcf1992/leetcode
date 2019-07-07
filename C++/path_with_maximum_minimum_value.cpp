/*
1102. Path With Maximum Minimum Value
Given a matrix of integers A with R rows and C columns, find the maximum score of a path starting at [0,0] and ending at [R-1,C-1].

The score of a path is the minimum value in that path.  For example, the value of the path 8 →  4 →  5 →  9 is 4.

A path moves some number of times from one visited cell to any neighbouring unvisited cell in one of the 4 cardinal directions (north, east, west, south).



Example 1:



Input: [[5,4,5],[1,2,6],[7,4,6]]
Output: 4
Explanation:
The path with the maximum score is highlighted in yellow.
Example 2:



Input: [[2,2,1,2,2,2],[1,2,2,2,1,2]]
Output: 2
Example 3:



Input: [[3,4,6,3,4],[0,2,1,1,7],[8,8,3,2,7],[3,2,4,9,8],[4,1,2,0,0],[4,6,5,4,3]]
Output: 3


Note:

1 <= R, C <= 100
0 <= A[i][j] <= 10^9

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
#include <set>
#include <numeric>
using namespace std;

struct Move { // {height, row, col}
    int v;
    int r;
    int c;

    Move(int a, int b, int c) : v (a), r (b), c (c) {}

    bool operator< (const Move& m) const {
        return v < m.v;
    }
};

class Solution {
public:
    int maximumMinimumPath(vector<vector<int>>& A) {
        int m = A.size();
        if (m == 0) {
            return 0;
        }
        int n = A[0].size();

        priority_queue<Move> pq;
        pq.push(Move(A[0][0], 0, 0));
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        visited[0][0] = true;

        int result = INT_MAX;
        vector<int> diff({0, 1, 0, -1, 0});
        while (!pq.empty()) {
            Move move = pq.top();
            pq.pop();

            result = min(result, move.v);
            if (move.r == m - 1 and move.c == n - 1) {
                return result;
            }

            for (int i = 1; i < diff.size(); ++i) {
                int row = move.r + diff[i];
                int col = move.c + diff[i - 1];
                if (row >= 0 and row < m and col >= 0 and col < n and !visited[row][col]) {
                    visited[row][col] = true;
                    pq.push(Move(A[row][col], row, col));
                }
            }
        }
        return -1;
    }
};
