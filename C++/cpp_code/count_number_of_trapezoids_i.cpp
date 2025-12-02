/*
https://leetcode.com/problems/count-number-of-trapezoids-i/description/
3623. Count Number of Trapezoids I

You are given a 2D integer array points, where points[i] = [xi, yi] represents the coordinates of the ith point on the
Cartesian plane.

A horizontal trapezoid is a convex quadrilateral with at least one pair of horizontal sides (i.e. parallel to the
x-axis). Two lines are parallel if and only if they have the same slope.

Return the number of unique horizontal trapezoids that can be formed by choosing any four distinct points from points.

Since the answer may be very large, return it modulo 109 + 7.



Example 1:

Input: points = [[1,0],[2,0],[3,0],[2,2],[3,2]]

Output: 3

Explanation:



There are three distinct ways to pick four points that form a horizontal trapezoid:

Using points [1,0], [2,0], [3,2], and [2,2].
Using points [2,0], [3,0], [3,2], and [2,2].
Using points [1,0], [3,0], [3,2], and [2,2].
Example 2:

Input: points = [[0,0],[1,0],[0,1],[2,1]]

Output: 1

Explanation:



There is only one horizontal trapezoid that can be formed.



Constraints:

4 <= points.length <= 105
–108 <= xi, yi <= 108
All points are pairwise distinct.
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
using namespace std;

class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        const int mod = 1e9 + 7;

        unordered_map<int, int> point_cnt;
        for (auto& point : points) {
            point_cnt[point[1]] += 1;
        }

        long long rst = 0;
        long long sum = 0;
        for (auto& [_, cnt] : point_cnt) {
            long long edge = (long long)cnt * (cnt - 1) / 2;
            rst += edge * sum;
            sum += edge;
        }
        return rst % mod;
    }
};
