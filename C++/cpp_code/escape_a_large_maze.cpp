/*
1036. Escape a Large Maze

In a 1 million by 1 million grid,

the coordinates of each grid square are (x, y) with 0 <= x, y < 10^6.
We start at the source square and want to reach the target square.

Each move, we can walk to a 4-directionally adjacent square in the grid that isn't in the given list of blocked squares.
Return true if and only if it is possible to reach the target square through a sequence of moves.

Example 1:
Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
Output: false
Explanation:
The target square is inaccessible starting from the source square, because we can't walk outside the grid.

Example 2:
Input: blocked = [], source = [0,0], target = [999999,999999]
Output: true
Explanation:
Because there are no blocked cells, it's possible to reach the target square.

Note:
0 <= blocked.length <= 200
blocked[i].length == 2
0 <= blocked[i][j] < 10^6
source.length == target.length == 2
0 <= source[i][j], target[i][j] < 10^6
source != target
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
using namespace std;
/*
https://leetcode.com/problems/escape-a-large-maze/discuss/282849/Python-Maximum-Blocked-19900-(Video)
Simple BFS problem, but as the search space is very big, so it can easily get time limit exceeded.

Cause there are two cases for this problem:
1. if we can find a path from source to target, then return true
2. if we cannnot find return false; But if it reach 20000 steps we return true;

The only possible case that source cannot reach target is that source or target is sorrounded by the blocks,
and the largest area 200 blocks(according to the limits) can form is
In case people are wondering where he get the 19900 area, the calculation is done by
using one of the corner as wall and placing a perfectly diagonal line of block across.
This maximizing the area covered while only using certain amount of block (200 in this case)

The sum of the area available equals 1+2+3+4+5+...+198+199=(1+199)*199/2=19900 (trapezoid sum)
0th     _________________________
    |-------------------- X
    |-------------------X
    |                .
    |             .
    .           .
    .        X
    .    X
200    | X
*/
/*
The maximum area is not 10000. Even it's accepted with bound 10000, it's wrong.
All cells are discrete, so there is nothing to do with pi.
It maximum blocked is achieved when the blocked squares surround one of the corners as a 45-degree straight line.

And it's easily proved.

If two cells are connected horizontally,
we can slide one part vertically to get bigger area.

If two cells are connected vertically,
we can slide one part horizontally to get bigger area.

Two connected cells,
no matter horizontally or vertically connected,
will surround smaller area than the way of 45-degree connected.
*/
class Solution {
private:
    int length = 1e6;
    vector<int> rDiff = {0, 0, 1, -1};
    vector<int> cDiff = {1, -1, 0, 0};

    bool search(vector<int>& source, vector<int>& target, unordered_map<int, unordered_map<int, bool>>& blocked) {
        unordered_map<int, unordered_map<int, bool>> visited;
        visited[source[0]][source[1]] = true;
        queue<pair<int, int>> bfs;
        bfs.push({source[0], source[1]});
        int area = 1;
        while (!bfs.empty()) {
            int r = bfs.front().first;
            int c = bfs.front().second;
            bfs.pop();
            if ((r == target[0] and c == target[1]) or area == 20000) {
                return true;
            }

            for (int i = 0; i < 4; ++i) {
                int nr = r + rDiff[i];
                int nc = c + cDiff[i];
                if (nr >= 0 and nr < length and nc >= 0 and nc < length and !visited[nr][nc] and !blocked[nr][nc]) {
                    area += 1;
                    bfs.push({nr, nc});
                    visited[nr][nc] = true;
                }
            }
        }
        return false;
    }

public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        unordered_map<int, unordered_map<int, bool>> blocks;
        for (vector<int>& b : blocked) {
            blocks[b[0]][b[1]] = true;
        }
        return search(source, target, blocks) and search(target, source, blocks);
    }
};