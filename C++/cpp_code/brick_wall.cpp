/*
554. Brick Wall
https://leetcode.com/problems/brick-wall/

There is a brick wall in front of you.
The wall is rectangular and has several rows of bricks.
The bricks have the same height but different width.
You want to draw a vertical line from the top to the bottom and cross the least bricks.

The brick wall is represented by a list of rows.
Each row is a list of integers representing the width of each brick in this row from left to right.

If your line go through the edge of a brick,
then the brick is not considered as crossed.
You need to find out how to draw the line to cross the least bricks and return the number of crossed bricks.

You cannot draw a line just along one of the two vertical edges of the wall,
in which case the line will obviously cross no bricks.

Example:
Input: [[1,2,2,1],
        [3,1,2],
        [1,3,2],
        [2,4],
        [3,1,2],
        [1,3,1,1]]

Output: 2
Explanation:

Note:
The width sum of bricks in different rows are the same and won't exceed INT_MAX.
The number of bricks in each row is in range [1,10,000].
The height of wall is in range [1,10,000].
Total number of bricks of the wall won't exceed 20,000.
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
using namespace std;

class Solution {
public:
    int leastBricks(vector<vector<int> > &wall) {
        unordered_map<int, int> edges;
        int crossEdges = 0;
        for (int i = 0; i < wall.size(); i++) {
            int edge = 0;
            for (int j = 0; j < wall[i].size() - 1; j++) {
                edge += wall[i][j];
                edges[edge] += 1;
                crossEdges = max(crossEdges, edges[edge]);
            }
        }
        return wall.size() - crossEdges;
    }
};