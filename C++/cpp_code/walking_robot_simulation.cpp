/*
874. Walking Robot Simulation

A robot on an infinite grid starts at point (0, 0) and faces north.
The robot can receive one of three possible types of commands:
-2: turn left 90 degrees
-1: turn right 90 degrees
1 <= x <= 9: move forward x units
Some of the grid squares are obstacles.

The i-th obstacle is at grid point (obstacles[i][0], obstacles[i][1])

If the robot would try to move onto them, the robot stays on the previous grid square instead
(but still continues following the rest of the route.)
Return the square of the maximum Euclidean distance that the robot will be from the origin.

Example 1:
Input: commands = [4,-1,3], obstacles = []
Output: 25
Explanation: robot will go to (3, 4)

Example 2:
Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
Output: 65
Explanation: robot will be stuck at (1, 4) before turning left and going to (1, 8)

Note:
0 <= commands.length <= 10000
0 <= obstacles.length <= 10000
-30000 <= obstacle[i][0] <= 30000
-30000 <= obstacle[i][1] <= 30000
The answer is guaranteed to be less than 2 ^ 31.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
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
    pair<int, int> getNewDirection(pair<int, int> curDirection, int command) {
        int x = curDirection.first;
        int y = curDirection.second;
        if (x == 0 and y
        ==
        1
        )
        {
            return command == -1 ? make_pair(1, 0) : make_pair(-1, 0);
        }
        if (x == 0 and y
        ==
        -1
        )
        {
            return command == -1 ? make_pair(-1, 0) : make_pair(1, 0);
        }
        if (x == -1 and y
        ==
        0
        )
        {
            return command == -1 ? make_pair(0, 1) : make_pair(0, -1);
        }
        return command == -1 ? make_pair(0, -1) : make_pair(0, 1);
    }

public:
    int robotSim(vector<int> &commands, vector<vector<int> > &obstacles) {
        unordered_map<int, unordered_set<int> > obstacle;
        for (vector<int> &ob: obstacles) {
            obstacle[ob[0]].insert(ob[1]);
        }

        pair<int, int> curPos = {0, 0};
        pair<int, int> direction = {0, 1};
        int result = 0;
        for (int cmd: commands) {
            if (cmd == -2 or cmd
            ==
            -1
            )
            {
                direction = getNewDirection(direction, cmd);
                continue;
            }

            int x = curPos.first + direction.first;
            int y = curPos.second + direction.second;
            int move = 1;
            while (move < cmd and obstacle[x]
            .
            find(y) == obstacle[x].end()
            )
            {
                move += 1;
                x += direction.first;
                y += direction.second;
            }
            if (obstacle[x].find(y) != obstacle[x].end()) {
                x -= direction.first;
                y -= direction.second;
            }
            result = max(result, x * x + y * y);
            curPos = {x, y};
        }
        return result;
    }
};