/*
1041. Robot Bounded In Circle
https://leetcode.com/problems/robot-bounded-in-circle/

On an infinite plane, a robot initially stands at (0, 0) and faces north.
The robot can receive one of three instructions:

"G": go straight 1 unit;
"L": turn 90 degrees to the left;
"R": turn 90 degress to the right.
The robot performs the instructions given in order, and repeats them forever.

Return true if and only if there exists a circle in the plane such that the robot never leaves the circle.

Example 1:
Input: "GGLLGG"
Output: true
Explanation:
The robot moves from (0,0) to (0,2), turns 180 degrees, and then returns to (0,0).
When repeating these instructions, the robot remains in the circle of radius 2 centered at the origin.

Example 2:
Input: "GG"
Output: false
Explanation:
The robot moves north indefinitely.

Example 3:
Input: "GL"
Output: true
Explanation:
The robot moves from (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0, 0) -> ...

Note:
1 <= instructions.length <= 100
instructions[i] is in {'G', 'L', 'R'}
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
#include <map>
#include <numeric>
using namespace std;

// https://leetcode.com/problems/robot-bounded-in-circle/discuss/290856/JavaC%2B%2BPython-Let-Chopper-Help-Explain
class Solution {
public:
    bool isRobotBounded(string instructions) {
        int face = 0;
        int curX = 0;
        int curY = 0;
        vector<int> diffX({0, 1, 0, -1});
        vector<int> diffY({1, 0, -1, 0});
        for (char c : instructions) {
            if (c == 'G') {
                curX += diffX[face];
                curY += diffY[face];
            } else if (c == 'L') {
                face = (face + 3) % 4;
            } else {
                face = (face + 1) % 4;
            }
        }

        if (curX == 0 and curY == 0) {
            return true;
        }
        return face != 0;
    }
};