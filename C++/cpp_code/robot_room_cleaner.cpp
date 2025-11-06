/*
489. Robot Room Cleaner

Given a robot cleaner in a room modeled as a grid.
Each cell in the grid can be empty or blocked.
The robot cleaner with 4 given APIs can move forward, turn left or turn right.
Each turn it made is 90 degrees.
When it tries to move into a blocked cell, its bumper sensor detects the obstacle and it stays on the current cell.

Design an algorithm to clean the entire room using only the 4 given APIs shown below.

interface Robot {
// returns true if next cell is open and robot moves into the cell.
// returns false if next cell is obstacle and robot stays on the current cell.
boolean move();

// Robot will stay on the same cell after calling turnLeft/turnRight.
// Each turn will be 90 degrees.
void turnLeft();
void turnRight();

// Clean the current cell.
void clean();
}
Example:

Input:
room = [
[1,1,1,1,1,0,1,1],
[1,1,1,1,1,0,1,1],
[1,0,1,1,1,1,1,1],
[0,0,0,1,0,0,0,0],
[1,1,1,1,1,1,1,1]
],
row = 1,
col = 3

Explanation:
All grids in the room are marked by either 0 or 1.
0 means the cell is blocked, while 1 means the cell is accessible.
The robot initially starts at the position of row=1, col=3.
From the top left corner, its position is one row below and three columns right.

Notes:
The input is only given to initialize the room and the robot's position internally.
You must solve this problem "blindfolded".
In other words, you must control the robot using only the mentioned 4 APIs,
without knowing the room layout and the initial robot's position.
The robot's initial position will always be in an accessible cell.
The initial direction of the robot will be facing up.
All accessible cells are connected, which means the all cells marked as 1 will be accessible by the robot.
Assume all four edges of the grid are all surrounded by wall.
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

class Robot {
public:
    // Returns true if the cell in front is open and robot moves into the cell.
    // Returns false if the cell in front is blocked and robot stays in the current cell.
    bool move();

    // Robot will stay in the same cell after calling turnLeft/turnRight.
    // Each turn will be 90 degrees.
    void turnLeft();

    void turnRight();

    // Clean the current cell.
    void clean();
};

class Solution {
    // dfs
private:
    int x = 0;
    int y = 0;
    vector<int> dx = {0, 1, 0, -1};
    vector<int> dy = {1, 0, -1, 0};
    int direct = 0;
    unordered_map<int, unordered_map<int, int>> visited;

public:
    void cleanRoom(Robot& robot) {
        if (visited[x][y] == 1) {
            return;
        }

        visited[x][y] = 1;
        robot.clean();
        for (int i = 0; i < 4; i++) {
            if (robot.move()) {
                x += dx[direct];
                y += dy[direct];
                cleanRoom(robot);
                robot.turnRight();
                robot.turnRight();
                robot.move();
                robot.turnLeft();
                robot.turnLeft();
                x -= dx[direct];
                y -= dy[direct];
            }
            robot.turnRight();
            direct = (direct + 1) % 4;
        }
    }
};