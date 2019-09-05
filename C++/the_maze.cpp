/*
 490. The Maze
 There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right,
 but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

 Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.

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

 Output: true
 Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.

 Example 2

 Input 1: a maze represented by a 2D array

 0 0 1 0 0
 0 0 0 0 0
 0 0 0 1 0
 1 1 0 1 1
 0 0 0 0 0

 Input 2: start coordinate (rowStart, colStart) = (0, 4)
 Input 3: destination coordinate (rowDest, colDest) = (3, 2)

 Output: false
 Explanation: There is no way for the ball to stop at the destination.

 Note:
 There is only one ball and one destination in the maze.
 Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
 The given maze does not contain border (like the red rectangle in the example pictures),
 but you could assume the border of the maze are all walls.
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
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size();
        int n = maze[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        queue<pair<int, int>> position;
        position.push({start[0], start[1]});
        while (!position.empty()) {
            pair<int, int> curPos = position.front();
            position.pop();

            int row = curPos.first;
            int col = curPos.second;
            visited[row][col] = true;
            if (row == destination[0] and col == destination[1]) {
                return true;
            }
            // move down
            while (row + 1 < m && maze[row + 1][col] != 1) {
                row += 1;
            }
            if (!visited[row][col]) {
                position.push({row, col});
            }
            //move up
            row = curPos.first;
            while (row - 1 >= 0 && maze[row - 1][col] != 1) {
                row -= 1;
            }
            if (!visited[row][col]) {
                position.push({row, col});
            }
            // move left
            row = curPos.first;
            while (col + 1 < n && maze[row][col + 1] != 1) {
                col += 1;
            }
            if (!visited[row][col]) {
                position.push({row, col});
            }

            //move right
            col = curPos.second;
            while (col - 1 >= 0 && maze[row][col - 1] != 1) {
                col -= 1;
            }
            if (!visited[row][col]) {
                position.push({row, col});
            }
        }
        return false;
    }
};
