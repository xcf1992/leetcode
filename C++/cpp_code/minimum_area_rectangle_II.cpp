/*
963. Minimum Area Rectangle II

Given a set of points in the xy-plane,
determine the minimum area of any rectangle formed from these points,
with sides not necessarily parallel to the x and y axes.

If there isn't any rectangle, return 0.

Example 1:

Input: [[1,2],[2,1],[1,0],[0,1]]
Output: 2.00000
Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.
Example 2:



Input: [[0,1],[2,1],[1,1],[1,0],[2,0]]
Output: 1.00000
Explanation: The minimum area rectangle occurs at [1,0],[1,1],[2,1],[2,0], with an area of 1.
Example 3:



Input: [[0,3],[1,2],[3,1],[1,3],[2,1]]
Output: 0
Explanation: There is no possible rectangle to form from these points.
Example 4:



Input: [[3,1],[1,1],[0,1],[2,1],[3,3],[3,2],[0,2],[2,3]]
Output: 2.00000
Explanation: The minimum area rectangle occurs at [2,1],[2,3],[3,3],[3,1], with an area of 2.


Note:

1 <= points.length <= 50
0 <= points[i][0] <= 40000
0 <= points[i][1] <= 40000
All points are distinct.
Answers within 10^-5 of the actual value will be accepted as correct.
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

/*
Intuition

Consider opposite points AC and BD of a rectangle ABCD.
They both have the same center O,
which is the midpoint of AC and the midpoint of AB;
and they both have the same radius dist(O, A) == dist(O, B) == dist(O, C) == dist(O, D).
Notice that a necessary and sufficient condition to form a rectangle with two opposite pairs of points
is that the points must have the same center and radius.

Motivated by that result,
let's classify each pair of points PQ by their center C = the midpoint of PQ,
and the radius r = dist(P, C).
Our strategy is to brute force on pairs of points with the same classification.

Algorithm

For each pair of points,
classify them by center and radius.
We only need to record one of the points P,
since the other point is P' = 2 * center - P (using vector notation).

For each center and radius,
look at every possible rectangle (two pairs of points P, P', Q, Q').
The area of this rectangle dist(P, Q) * dist(P, Q') is a candidate answer.
*/
class Solution {
private:
    double getDistance(int p1, int p2, vector<vector<int>>& points) {
        double distance = pow(points[p1][0] - points[p2][0], 2) + pow(points[p1][1] - points[p2][1], 2);
        return sqrt(distance);
    }

public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();
        unordered_map<string, vector<pair<int, int>>> memo;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double centerX = points[i][0] + points[j][0];
                double centerY = points[i][1] + points[j][1];
                double radius = getDistance(i, j, points);
                string key = to_string(centerX) + "_" + to_string(centerY) + "_" + to_string(radius);
                memo[key].push_back({i, j});
            }
        }

        double result = 0.0;
        for (auto it = memo.begin(); it != memo.end(); it++) {
            vector<pair<int, int>> pList = it->second;
            int len = pList.size();
            for (int i = 0; i < len; i++) {
                for (int j = i + 1; j < len; j++) {
                    int p1 = pList[i].first;
                    int p2 = pList[i].second;
                    int p3 = pList[j].first;
                    double area = getDistance(p1, p3, points) * getDistance(p2, p3, points);
                    if (result == 0.0 or result > area) {
                        result = area;
                    }
                }
            }
        }
        return result;
    }
};