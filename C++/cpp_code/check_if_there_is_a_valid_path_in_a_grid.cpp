/*
1391. Check if There is a Valid Path in a Grid
https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/

Given a m x n grid. Each cell of the grid represents a street. The street of grid[i][j] can be:
1 which means a street connecting the left cell and the right cell.
2 which means a street connecting the upper cell and the lower cell.
3 which means a street connecting the left cell and the lower cell.
4 which means a street connecting the right cell and the lower cell.
5 which means a street connecting the left cell and the upper cell.
6 which means a street connecting the right cell and the upper cell.


You will initially start at the street of the upper-left cell (0,0).
A valid path in the grid is a path which starts from the upper left cell (0,0)
and ends at the bottom-right cell (m - 1, n - 1).
The path should only follow the streets.

Notice that you are not allowed to change any street.
Return true if there is a valid path in the grid or false otherwise.

Example 1:
Input: grid = [[2,4,3],[6,5,2]]
Output: true
Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).

Example 2:
Input: grid = [[1,2,1],[1,2,1]]
Output: false
Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get
stuck at cell (0, 0)

Example 3:
Input: grid = [[1,1,2]]
Output: false
Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).

Example 4:
Input: grid = [[1,1,1,1,1,1,3]]
Output: true

Example 5:
Input: grid = [[2],[2],[2],[2],[2],[2],[6]]
Output: true

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 300
1 <= grid[i][j] <= 6
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

using namespace std;
/*
https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/solutions/547225/c-with-picture-track-direction-upscaled-e7oa1/?envType=company&envId=robinhood&favoriteSlug=robinhood-all
This is inspired by a similar solution for 959. Regions Cut By Slashes.

We can upscale the input grid to [n * 3][n * 3] grid and draw "roads" there. Then, we use DFS to trace the way from
start to finish. Picture below says it all. Thanks gaurav_ec for pushing the idea!

image
 */
class Solution {
private:
    bool dfs(vector<vector<bool>>& board, int i, int j) {
        if (min(i, j) < 0 || i >= board.size() || j >= board[i].size() || !board[i][j]) {
            return false;
        }

        if (i == board.size() - 2 && j == board[i].size() - 2) {
            return true;
        }

        board[i][j] = false;
        return dfs(board, i - 1, j) || dfs(board, i + 1, j) || dfs(board, i, j + 1) || dfs(board, i, j - 1);
    }

public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> board(m * 3, vector<bool>(n * 3));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int type = grid[i][j];
                board[i * 3 + 1][j * 3 + 1] = true;
                board[i * 3 + 1][j * 3 + 0] = type == 1 || type == 3 || type == 5;
                board[i * 3 + 1][j * 3 + 2] = type == 1 || type == 4 || type == 6;
                board[i * 3 + 0][j * 3 + 1] = type == 2 || type == 5 || type == 6;
                board[i * 3 + 2][j * 3 + 1] = type == 2 || type == 3 || type == 4;
            }
        }
        return dfs(board, 1, 1);
    }
};

/*
https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/solutions/547229/python-union-find-by-lee215-cea6/?envType=company&envId=robinhood&favoriteSlug=robinhood-all
Explanation
Assume we have input A[2][2]. (Thanks @Gad2017 for this diagram)
diagram

The center of A[0][0] has coordinates [0, 0]
The center of A[i][j] has coordinates [2i, 2j]
The top edge of A[i][j] has coordinates [2i-1, 2j]
The left edge of A[i][j] has coordinates [2i, 2j-1]
The bottom edge of A[i][j] has coordinates [2i+1, 2j]
The right edge of A[i][j] has coordinates [2i, 2j+1]

Then we apply Union Find:
if A[i][j] in [2, 5, 6]: connect center and top
if A[i][j] in [1, 3, 5]: connect center and left
if A[i][j] in [2, 3, 4]: connect center and bottom
if A[i][j] in [1, 4, 6]: connect center and right


Complexity
Time O(MN) * O(UF)
Space O(MN)
*/
class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        vector<vector<vector<int>>> directs({{{0, -1}, {0, 1}},
                                             {{-1, 0}, {1, 0}},
                                             {{0, -1}, {1, 0}},
                                             {{0, 1}, {1, 0}},
                                             {{0, -1}, {-1, 0}},
                                             {{0, 1}, {-1, 0}}});

        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<vector<int>> bfs;
        bfs.push({0, 0});
        visited[0][0] = true;
        while (!bfs.empty()) {
            int row = bfs.front()[0];
            int col = bfs.front()[1];
            bfs.pop();

            int type = grid[row][col] - 1;
            for (auto& dir : directs[type]) {
                int nr = row + dir[0];
                int nc = col + dir[1];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n || visited[nr][nc]) {
                    continue;
                }

                for (auto& backDir : directs[grid[nr][nc] - 1])
                    if (nr + backDir[0] == row and nc + backDir[1] == col) {
                        visited[nr][nc] = true;
                        bfs.push({nr, nc});
                    }
            }
        }
        return visited[m - 1][n - 1];
    }
};