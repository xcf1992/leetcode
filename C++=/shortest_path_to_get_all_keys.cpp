/*
864. Shortest Path to Get All Keys

We are given a 2-dimensional grid. "." is an empty cell, "#" is a wall, "@" is the starting point,
("a", "b", ...) are keys,
and ("A", "B", ...) are locks.

We start at the starting point,
and one move consists of walking one space in one of the 4 cardinal directions.
We cannot walk outside the grid, or walk into a wall.
If we walk over a key, we pick it up.
We can't walk over a lock unless we have the corresponding key.

For some 1 <= K <= 6,
there is exactly one lowercase and one uppercase letter of the first K letters of the English alphabet in the grid.
This means that there is exactly one key for each lock,
and one lock for each key;
and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.

Return the lowest number of moves to acquire all keys.
If it's impossible, return -1.

Example 1:
Input: ["@.a.#","###.#","b.A.B"]
Output: 8

Example 2:
Input: ["@..aA","..B#.","....b"]
Output: 6

Note:
1 <= grid.length <= 30
1 <= grid[0].length <= 30
grid[i][j] contains only '.', '#', '@', 'a'-'f' and 'A'-'F'
The number of keys is in [1, 6].  Each key has a different letter and opens exactly one lock.
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
#include <numeric>
using namespace std;

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size();
        if (m == 0) {
            return -1;
        }
        int n = grid[0].size();

        unordered_map<int, unordered_set<int>> visited;
        queue<pair<int, int>> bfs; // {curPos, key-bit-mask}
        int target = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '@') {
                    bfs.push({i * n + j, 0});
                    visited[i * n + j].insert(0);
                }
                else if (grid[i][j] >= 'A' and grid[i][j] <= 'F') {
                    target |= (1 << (grid[i][j] - 'A'));
                }
            }
        }

        vector<int> rDiff = {0, 0, 1, -1};
        vector<int> cDiff = {1, -1, 0, 0};
        int step = 0;
        while (!bfs.empty()) {
            int curSize = bfs.size();
            for (int i = 0; i < curSize; i++) {
                int row = bfs.front().first / n;
                int col = bfs.front().first % n;
                int keyMask = bfs.front().second;
                bfs.pop();

                if (keyMask == target) {
                    return step;
                }

                for (int d = 0; d < 4; d++) {
                    int nr = row + rDiff[d];
                    int nc = col + cDiff[d];
                    int have = keyMask;
                    if (nr < 0 or nr >= m or nc < 0 or nc >= n or grid[nr][nc] == '#') {
                        continue;
                    }

                    if (grid[nr][nc] >= 'A' and grid[nr][nc] <= 'F') {
                        int key = 1 << (grid[nr][nc] - 'A');
                        if (!(have & key)) {
                            continue;
                        }
                    }
                    else if (grid[nr][nc] >= 'a' and grid[nr][nc] <= 'f') {
                        have |= 1 << (grid[nr][nc] - 'a');
                    }
                    
                    int pos = nr * n + nc;
                    if (visited.find(pos) == visited.end() or visited[pos].find(have) == visited[pos].end()) {
                        visited[pos].insert(have);
                        bfs.push({pos, have});
                    }
                }
            }
            step += 1;
        }
        return -1;
    }
};
