/*
 994. Rotting Oranges

 In a given grid, each cell can have one of three values:
 
 the value 0 representing an empty cell;
 the value 1 representing a fresh orange;
 the value 2 representing a rotten orange.
 Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.
 
 Return the minimum number of minutes that must elapse until no cell has a fresh orange.  If this is impossible, return -1 instead.
 
 
 
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
    int orangesRotting(vector<vector<int>>& grid) {
        int fresh = 0;
        int m = grid.size();
        int n = grid[0].size();
        queue<int> bfs;
        vector<bool> visited(m * n + 1, false);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fresh += 1;
                }
                else if (grid[i][j] == 2) {
                    bfs.push(i * n + j);
                    visited[i * n + j] = true;
                }
            }
        }
        
        int time = 0;
        while (!bfs.empty() and fresh != 0) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int row = bfs.front() / n;
                int col = bfs.front() % n;
                bfs.pop();
                
                if (row + 1 < m and grid[row + 1][col] == 1 and !visited[(row + 1) * n + col]) {
                    grid[row + 1][col] = 2;
                    visited[(row + 1) * n + col] = true;
                    fresh -= 1;
                    bfs.push((row + 1) * n + col);
                }
                if (row - 1 >= 0 and grid[row - 1][col] == 1 and !visited[(row - 1) * n + col]) {
                    grid[row - 1][col] = 2;
                    visited[(row - 1) * n + col] = true;
                    fresh -= 1;
                    bfs.push((row - 1) * n + col);
                }
                if (col + 1 < n and grid[row][col + 1] == 1 and !visited[row * n + col + 1]) {
                    grid[row][col + 1] = 2;
                    visited[row * n + col + 1] = true;
                    fresh -= 1;
                    bfs.push(row * n + col + 1);
                }
                if (col - 1 >= 0 and grid[row][col - 1] == 1 and !visited[row * n + col - 1]) {
                    grid[row][col - 1] = 2;
                    visited[row * n + col - 1] = true;
                    fresh -= 1;
                    bfs.push(row * n + col - 1);
                }
            }
            time += 1;
        }
        return fresh == 0 ? time : -1;
    }
};
