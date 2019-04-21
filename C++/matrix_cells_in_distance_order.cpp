/*
 1030. Matrix Cells in Distance Order

 We are given a matrix with R rows and C columns has cells with integer coordinates (r, c), where 0 <= r < R and 0 <= c < C.
 
 Additionally, we are given a cell in that matrix with coordinates (r0, c0).
 
 Return the coordinates of all cells in the matrix, sorted by their distance from (r0, c0) from smallest distance to largest distance.  Here, the distance between two cells (r1, c1) and (r2, c2) is the Manhattan distance, |r1 - r2| + |c1 - c2|.  (You may return the answer in any order that satisfies this condition.)
 
 
 
 Example 1:
 
 Input: R = 1, C = 2, r0 = 0, c0 = 0
 Output: [[0,0],[0,1]]
 Explanation: The distances from (r0, c0) to other cells are: [0,1]
 Example 2:
 
 Input: R = 2, C = 2, r0 = 0, c0 = 1
 Output: [[0,1],[0,0],[1,1],[1,0]]
 Explanation: The distances from (r0, c0) to other cells are: [0,1,1,2]
 The answer [[0,1],[1,1],[0,0],[1,0]] would also be accepted as correct.
 Example 3:
 
 Input: R = 2, C = 3, r0 = 1, c0 = 2
 Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
 Explanation: The distances from (r0, c0) to other cells are: [0,1,1,2,2,3]
 There are other answers that would also be accepted as correct, such as [[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]].
 
 
 Note:
 
 1 <= R <= 100
 1 <= C <= 100
 0 <= r0 < R
 0 <= c0 < C
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
private:
    vector<int> dx{0, 0, 1, -1};
    vector<int> dy{1, -1, 0, 0};
public:
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        vector<vector<int>> result;
        queue<vector<int>> bfs;
        bfs.push({r0, c0});
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        visited[r0][c0] = true;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                vector<int> cur = bfs.front();
                bfs.pop();
                
                result.push_back(cur);
                for (int j = 0; j < 4; ++j) {
                    int nr = cur[0] + dx[j];
                    int nc = cur[1] + dy[j];
                    if (nr >= 0 and nc >= 0 and nr < R and nc < C and !visited[nr][nc]) {
                        bfs.push({nr, nc});
                        visited[nr][nc] = true;
                    }
                }
            }
        }
        return result;
    }
};
