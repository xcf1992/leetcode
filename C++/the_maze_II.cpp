/*
 There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, 
 but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
 
 Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. 
 The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). 
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
 Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
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
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size();
        int n = maze[0].size();
        
        queue<pair<int, int>> position;
        vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
        position.push(make_pair(start[0], start[1]));
        distance[start[0]][start[1]] = 0;
        
        int result = INT_MAX;
        while (!position.empty()) {
            pair<int, int> curPos = position.front();
            position.pop();
            
            int curX = curPos.first;
            int curY = curPos.second;
            int curDis = distance[curX][curY];
            if (curX == destination[0] && curY == destination[1]) {
                result = min(result, curDis);
                continue;
            }
            
            // move down
            int move = 0;
            while (curX + 1 < m && maze[curX + 1][curY] != 1) {
                curX += 1;
                move += 1;
            }
            if (distance[curX][curY] > curDis + move) {
                distance[curX][curY] = curDis + move;
                position.push(make_pair(curX, curY));
            }
            
            //move up
            curX = curPos.first;
            move = 0;
            while (curX - 1 >= 0 && maze[curX - 1][curY] != 1) {
                curX -= 1;
                move += 1;
            }
            if (distance[curX][curY] > curDis + move) {
                distance[curX][curY] = curDis + move;
                position.push(make_pair(curX, curY));
            }
            
            // move left
            curX = curPos.first;
            move = 0;
            while (curY + 1 < n && maze[curX][curY + 1] != 1) {
                curY += 1;
                move += 1;
            }
            if (distance[curX][curY] > curDis + move) {
                distance[curX][curY] = curDis + move;
                position.push(make_pair(curX, curY));
            }
            
            //move right
            curY = curPos.second;
            move = 0;
            while (curY - 1 >= 0 && maze[curX][curY - 1] != 1) {
                curY -= 1;
                move += 1;
            }
            if (distance[curX][curY] > curDis + move) {
                distance[curX][curY] = curDis + move;
                position.push(make_pair(curX, curY));
            }
        }
        
        return result == INT_MAX ? -1 : result;
    }
};
