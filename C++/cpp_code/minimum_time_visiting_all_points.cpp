/*
1266. Minimum Time Visiting All Points
https://leetcode.com/problems/minimum-time-visiting-all-points/

On a plane there are n points with integer coordinates points[i] = [xi, yi].
Your task is to find the minimum time in seconds to visit all points.

You can move according to the next rules:
In one second always you can either move vertically,
horizontally by one unit or diagonally (it means to move one unit vertically and one unit horizontally in one second).
You have to visit the points in the same order as they appear in the array.

Example 1:
Input: points = [[1,1],[3,4],[-1,0]]
Output: 7
Explanation: One optimal path is [1,1] -> [2,2] -> [3,3] -> [3,4] -> [2,3] -> [1,2] -> [0,1] -> [-1,0]
Time from [1,1] to [3,4] = 3 seconds
Time from [3,4] to [-1,0] = 4 seconds
Total time = 7 seconds

Example 2:
Input: points = [[3,2],[-2,2]]
Output: 5

Constraints:
points.length == n
1 <= n <= 100
points[i].length == 2
-1000 <= points[i][0], points[i][1] <= 1000
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
#include "extra_data_types.hpp"
using namespace std;
/*
Intuition

In order to minimize steps, we should walk most points diagonally.
If we cannot make a move then those points should be covered either horizontally or vertically.

Example : Lets say |x2 - x1| = 5 and |y2 - y1| = 3,
then we would walk 3 diagonally and remaining two have to be walked horizontally.
*/
class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int> > &points) {
        int n = points.size();
        if (n <= 1) {
            return 0;
        }

        int result = 0;
        for (int i = 1; i < n; ++i) {
            result += max(abs(points[i][0] - points[i - 1][0]), abs(points[i][1] - points[i - 1][1]));
        }
        return result;
    }
};