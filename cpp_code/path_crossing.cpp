/*
1496. Path Crossing
https://leetcode.com/problems/path-crossing/

Given a string path,
where path[i] = 'N', 'S', 'E' or 'W',
each representing moving one unit north, south, east, or west, respectively.
You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.

Return True if the path crosses itself at any point,
that is, if at any time you are on a location you've previously visited. Return False otherwise.

Example 1:
Input: path = "NES"
Output: false
Explanation: Notice that the path doesn't cross any point more than once.

Example 2:
Input: path = "NESWW"
Output: true
Explanation: Notice that the path visits the origin twice.

Constraints:
1 <= path.length <= 10^4
path will only consist of characters in {'N', 'S', 'E', 'W}
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
#include <set>
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    bool isPathCrossing(string path) {
        int curX = 0;
        int curY = 0;
        unordered_set<string> visited;
        visited.insert(to_string(curX) + "_" + to_string(curY));
        for (char c : path) {
            if (c == 'N') {
                curY += 1;
            }
            else if (c == 'S') {
                curY -= 1;
            }
            else if (c == 'E') {
                curX += 1;
            }
            else if (c == 'W') {
                curX -= 1;
            }

            string pos = to_string(curX) + "_" + to_string(curY);
            if (visited.find(pos) == visited.end()) {
                visited.insert(pos);
            }
            else {
                return true;
            }
        }
        return false;
    }
};
