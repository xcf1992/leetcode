/*
505. The Maze II
https://leetcode.com/problems/the-maze-ii/

There is a ball in a maze with empty spaces and walls.
The ball can go through empty spaces by rolling up, down, left or right,
but it won't stop rolling until hitting a wall.
When the ball stops, it could choose the next direction.

Given the ball's start bfs, the destination and the maze,
find the shortest distance for the ball to stop at the destination.

The distance is defined by the number of empty spaces traveled by the ball
from the start bfs (excluded) to the destination (included).
If the ball cannot stop at the destination, return -1.

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space.
You may assume that the borders of the maze are all walls.
The start and destination coordinates are represented by row and column indexes.

Example 1
Input 1: a maze represented by a 2D array
0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0
Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (4, 4)
Output: 12
Explanation: One shortest way is : left -> down -> left -> down -> right -> down -> right.
The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.

Example 2
Input 1: a maze represented by a 2D array
0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0
Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (3, 2)
Output: -1
Explanation: There is no way for the ball to stop at the destination.

Note:
There is only one ball and one destination in the maze.
Both the ball and the destination exist on an empty space, and they will not be at the same bfs initially.
The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.
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
#include <set>
using namespace std;

class Solution {
private:
    int m = 0;
    int n = 0;
    vector<int> rDiff = {-1, 1, 0, 0};
    vector<int> cDiff = {0, 0, -1, 1};

    bool isValid(int row, int col) {
        return row >= 0
        and col
        >=
        0
        and row<m and col < n;
    }

public:
    int shortestDistance(vector<vector<int> > &maze, vector<int> &start, vector<int> &destination) {
        m = maze.size();
        n = maze[0].size();

        queue<pair<int, int> > bfs;
        bfs.push({start[0], start[1]});
        vector<vector<int> > distance(m, vector<int>(n, INT_MAX));
        distance[start[0]][start[1]] = 0;

        int result = INT_MAX;
        while (!bfs.empty()) {
            pair<int, int> curPos = bfs.front();
            bfs.pop();

            int row = curPos.first;
            int col = curPos.second;
            int curDis = distance[row][col];
            if (row == destination[0] and col
            ==
            destination[1]
            )
            {
                result = min(result, curDis);
                continue;
            }

            for (int i = 0; i < 4; i++) {
                row = curPos.first;
                col = curPos.second;
                int move = 0;

                while (isValid(row + rDiff[i], col + cDiff[i]) and maze[row + rDiff[i]][col + cDiff[i]]
                !=
                1
                )
                {
                    row += rDiff[i];
                    col += cDiff[i];
                    move += 1;
                }
                if (distance[row][col] > curDis + move) {
                    distance[row][col] = curDis + move;
                    bfs.push({row, col});
                }
            }
        }
        return result == INT_MAX ? -1 : result;
    }
};