/*
939. Minimum Area Rectangle
Given a set of points in the xy-plane,
determine the minimum area of a rectangle formed from these points,
with sides parallel to the x and y axes.

If there isn't any rectangle, return 0.

Example 1:

Input: [[1,1],[1,3],[3,1],[3,3],[2,2]]
Output: 4
Example 2:

Input: [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
Output: 2


Note:

1 <= points.length <= 500
0 <= points[i][0] <= 40000
0 <= points[i][1] <= 40000
All points are distinct.
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
#include <numeric>
using namespace std;

// Time complexity is n^2
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        map<int, vector<int>> x2Points;
        for (vector<int>& point : points) {
            x2Points[point[0]].push_back(point[1]);
        }

        int result = INT_MAX;
        unordered_map<int, int> memo;
        for (auto it = x2Points.begin(); it != x2Points.end(); it++) {
            int x = it->first;
            vector<int> yPoints = it->second;
            sort(yPoints.begin(), yPoints.end());
            for (int i = 0; i < yPoints.size() - 1; i++) {
                // we need to check every possible combination here
                for (int j = i + 1; j < yPoints.size(); j++) {
                    int y1 = yPoints[i];
                    int y2 = yPoints[j];
                    int code = 40001 * y1 + y2;
                    if (memo.find(code) != memo.end()) {
                        result = min(result, abs((memo[code] - x) * (y1 - y2)));
                    }
                    memo[code] = x;
                }
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};