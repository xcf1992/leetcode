/*
https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-i/description/
3380. Maximum Area Rectangle With Point Constraints I

You are given an array points where points[i] = [xi, yi] represents the coordinates of a point on an infinite plane.

Your task is to find the maximum area of a rectangle that:

Can be formed using four of these points as its corners.
Does not contain any other point inside or on its border.
Has its edges parallel to the axes.
Return the maximum area that you can obtain or -1 if no such rectangle is possible.



Example 1:

Input: points = [[1,1],[1,3],[3,1],[3,3]]

Output: 4

Explanation:

Example 1 diagram

We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border.
Hence, the maximum possible area would be 4.

Example 2:

Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]

Output: -1

Explanation:

Example 2 diagram

There is only one rectangle possible is with points [1,1], [1,3], [3,1] and [3,3] but [2,2] will always lie inside it.
Hence, returning -1.

Example 3:

Input: points = [[1,1],[1,3],[3,1],[3,3],[1,2],[3,2]]

Output: 2

Explanation:

Example 3 diagram

The maximum area rectangle is formed by the points [1,3], [1,2], [3,2], [3,3], which has an area of 2. Additionally, the
points [1,1], [1,2], [3,1], [3,2] also form a valid rectangle with the same area.



Constraints:

1 <= points.length <= 10
points[i].length == 2
0 <= xi, yi <= 100
All the given points are unique.
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
#include <set>
#include <numeric>
using namespace std;
/*
Intuition
To solve the problem, the key observation is that a rectangle can be defined by four points satisfying the following:

Two pairs of points have the same x-coordinates.
Two pairs of points have the same y-coordinates.
The goal is to find all such rectangles and compute their areas efficiently.

Approach
Sorting The Points
Sort the points lexicographically by their x-coordinates and then by y-coordinates. This helps group points with the
same x-coordinate together for easier rectangle identification. Iterate Through Points: For each point, consider it as a
potential bottom-left corner of a rectangle. Find the next three points that might form the rectangle: Two points should
share the same x-coordinates for the vertical sides. Two points should share the same y-coordinates for the horizontal
sides. Validate Rectangle: Use a helper function get to validate if the selected four points form a rectangle. If valid,
calculate the area using the formula: Area=(difference in x-coordinates)×(difference in y-coordinates) Keep Track of
Maximum Area: For each valid rectangle, update the maximum area if the current rectangle has a larger area.
*/
class Solution {
private:
    // Helper function to calculate the maximum rectangle area given four points
    int calc_area(vector<pair<int, int>>& points) {
        int rst = -1;
        for (int i = 0; i < points.size() - 3; i++) {
            // Check if these points can form a rectangle:
            // - First and second points have the same x-coordinate
            // - Third and fourth points have the same x-coordinate
            // - First and third points have the same y-coordinate
            // - Second and fourth points have the same y-coordinate
            if (points[i].first == points[i + 1].first && points[i + 2].first == points[i + 3].first &&
                points[i].second == points[i + 2].second && points[i + 1].second == points[i + 3].second) {
                // Calculate the area of the rectangle
                int area = (points[i + 2].first - points[i].first) * (points[i + 1].second - points[i].second);
                rst = max(rst, area);
            }
        }
        return rst;
    }

public:
    int maxRectangleArea(vector<vector<int>>& points) {
        // Sort the points by their x-coordinates and then by y-coordinates
        sort(points.begin(), points.end(),
             [](vector<int>& a, vector<int>& b) { return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]); });

        int rst = -1;
        int n = points.size();
        for (int i = 0; i < n - 3; i++) {
            if (points[i][0] != points[i + 1][0]) {
                continue;
            }

            // Add the first two points of the rectangle
            vector<pair<int, int>> rect_points;
            rect_points.push_back({points[i][0], points[i][1]});
            rect_points.push_back({points[i + 1][0], points[i + 1][1]});

            // Find the next two points that complete the rectangle
            int j = i + 2;
            while (j < n - 2) {
                // Skip points that don't align with the y-coordinates of the rectangle
                if (points[j][1] < points[i][1] || points[j][1] > points[i + 1][1]) {
                    j++;
                } else {
                    break;
                }
            }

            // Add the potential third and fourth points
            if (j < n - 1) {
                rect_points.push_back({points[j][0], points[j][1]});
                rect_points.push_back({points[j + 1][0], points[j + 1][1]});

                // Calculate the maximum area for this set of points
                rst = max(rst, calc_area(rect_points));
            }
        }

        return rst;
    }
};

class Solution {
public:
    bool isValid(vector<vector<int>>& points, int x1, int y1, int x2, int y2) {
        int cornerCount = 0;

        for (auto& p : points) {
            int x = p[0], y = p[1];

            // Skip points completely outside the rectangle
            if (x < x1 || x > x2 || y < y1 || y > y2)
                continue;

            // If it's exactly one of the 4 corners, count it
            if ((x == x1 || x == x2) && (y == y1 || y == y2)) {
                cornerCount++;
                continue;
            }

            // Otherwise, it's inside or on the border but not a corner
            // → this rectangle is invalid
            return false;
        }

        // Valid only if all 4 corners were found
        return cornerCount == 4;
    }
    int maxRectangleArea(vector<vector<int>>& points) {
        int n = points.size();
        int ans = -1;

        // Enumerate every pair of points as potential DIAGONAL corners
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // Derive the bounding rectangle
                int x1 = min(points[i][0], points[j][0]);  // left
                int y1 = min(points[i][1], points[j][1]);  // bottom
                int x2 = max(points[i][0], points[j][0]);  // right
                int y2 = max(points[i][1], points[j][1]);  // top

                // Skip degenerate cases (same row or same column → zero area)
                if (x1 == x2 || y1 == y2)
                    continue;

                // Check this candidate rectangle
                if (isValid(points, x1, y1, x2, y2)) {
                    ans = max(ans, (x2 - x1) * (y2 - y1));
                }
            }
        }
        return ans;
    }
};