/*
 994. Rotting Oranges

 In a given grid, each cell can have one of three values:

 the value 0 representing an empty cell;
 the value 1 representing a fresh orange;
 the value 2 representing a rotten orange.
 Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.

 Return the minimum number of minutes that must elapse until no cell has a fresh orange.
 If this is impossible, return -1 instead.

 Example 1:



 Input: [[2,1,1],[1,1,0],[0,1,1]]
 Output: 4
 Example 2:

 Input: [[2,1,1],[0,1,1],[1,0,1]]
 Output: -1
 Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
 Example 3:

 Input: [[0,2]]
 Output: 0
 Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.


 Note:

 1 <= grid.length <= 10
 1 <= grid[0].length <= 10
 grid[i][j] is only 0, 1, or 2.
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

class Solution {
public:
    int orangesRotting(vector<vector<int> > &grid) {
        int fresh = 0;
        int m = grid.size();
        int n = grid[0].size();
        queue<int> bfs;
        vector<bool> visited(m * n + 1, false);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fresh += 1;
                } else if (grid[i][j] == 2) {
                    bfs.push(i * n + j);
                    visited[i * n + j] = true;
                }
            }
        }

        int time = 0;
        vector<int> diff({0, 1, 0, -1, 0});
        while (!bfs.empty() and fresh
        !=
        0
        )
        {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int row = bfs.front() / n;
                int col = bfs.front() % n;
                bfs.pop();

                for (int i = 1; i < diff.size(); ++i) {
                    int nRow = row + diff[i];
                    int nCol = col + diff[i - 1];
                    if (nRow < m and nRow
                    >=
                    0
                    and nCol<n and nCol >= 0 and grid[nRow][nCol] == 1 and !visited[nRow * n + nCol]
                    )
                    {
                        grid[nRow][nCol] = 2;
                        visited[nRow * n + nCol] = true;
                        fresh -= 1;
                        bfs.push(nRow * n + nCol);
                    }
                }
            }
            time += 1;
        }
        return fresh == 0 ? time : -1;
    }
};