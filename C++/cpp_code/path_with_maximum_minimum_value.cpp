/*
1102. Path With Maximum Minimum Value
https://leetcode.com/problems/path-with-maximum-minimum-value/

Given a matrix of integers A with R rows and C columns,
find the maximum score of a path starting at [0,0] and ending at [R-1,C-1].

The score of a path is the minimum value in that path.
For example, the value of the path 8 →  4 →  5 →  9 is 4.

A path moves some number of times from one visited cell to any neighbouring unvisited cell in one of the 4 cardinal
directions (north, east, west, south).

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

struct myComp {
    bool operator()(vector<int>& a, vector<int>& b) {
        return a[2] < b[2];
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

        priority_queue<vector<int>, vector<vector<int>>, myComp> pq;
        pq.push({0, 0, A[0][0]});
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        visited[0][0] = true;

        int result = INT_MAX;
        vector<int> diff({0, 1, 0, -1, 0});
        while (!pq.empty()) {
            int row = pq.top()[0];
            int col = pq.top()[1];
            int val = pq.top()[2];
            pq.pop();

            result = min(result, val);
            if (row == m - 1 and col == n - 1) {
                return result;
            }

            for (int i = 1; i < diff.size(); ++i) {
                int nr = row + diff[i];
                int nc = col + diff[i - 1];
                if (nr >= 0 and nr < m and nc >= 0 and nc < n and !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    pq.push({nr, nc, A[nr][nc]});
                }
            }
        }
        return -1;
    }
};