/*
 469. Convex Polygon
 Given a list of points that form a polygon when joined sequentially,
 find if this polygon is convex (Convex polygon definition).

 Note:

 There are at least 3 and at most 10,000 points.
 Coordinates are in the range -10,000 to 10,000.
 You may assume the polygon formed by given points is always a simple polygon (Simple polygon definition). In other words, we ensure that exactly two edges intersect at each vertex, and that edges otherwise don't intersect each other.
 Example 1:

 [[0,0],[0,1],[1,1],[1,0]]

 Answer: True

 Explanation:
 Example 2:

 [[0,0],[0,10],[10,10],[10,0],[5,5]]

 Answer: False

 Explanation:
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
#include <numeric>
using namespace std;

/*
Great solution inspired by @Ipeq1! Here is a C++ version with extracted determinant calculation.

The key observation for convexity is that vector pi+1-pi always turns to the same direction to pi+2-pi formed by any 3 sequentially adjacent vertices, i.e., cross product (pi+1-pi) x (pi+2-pi) does not change sign when traversing sequentially along polygon vertices.

Note that for any 2D vectors v1, v2,

v1 x v2 = det([v1, v2])
which is the determinant of 2x2 matrix [v1, v2]. And the sign of det([v1, v2]) represents the positive z-direction of right-hand system from v1 to v2. So det([v1, v2]) ≥ 0 if and only if v1 turns at most 180 degrees counterclockwise to v2.
*/
class Solution {
private:
    // determinant of 2x2 matrix [A1-A0, A2-A0]
    long det2(const vector<vector<int>>& A) {
    	return (A[1][0]-A[0][0])*(A[2][1]-A[0][1]) - (A[1][1]-A[0][1])*(A[2][0]-A[0][0]);
    }
public:
    bool isConvex(vector<vector<int>>& p) {
      for (int i=0, pos=0, neg=0, n=p.size(); i < n; ++i) {
        long det = det2({p[i], p[(i+1)%n], p[(i+2)%n]});
        if ((pos|=(det>0))*(neg|=(det<0))) return false;
      }
      return true;
    }
};

class Solution1 {
private:
    // x2 y2 as base point and anti clock wise
    double getAngle(int x1, int y1, int x2, int y2) {
        if (x1 == x2) {
            return y1 > y2 ? 90 : 270;
        }
        if (y1 == y2) {
            return x1 > x2 ? 0 : 180;
        }

        int tmp = atan(abs(y1 - y2) / abs(x1 - x2)) * 180 / PI;
        if (x1 < x2 && y1 > y2){
            return 180 - tmp;
        }
        if (x1 < x2 && y1 < y2) {
            return 180 + tmp;
        }
        if (x1 > x2 && y1 < y2) {
            return 360 - tmp;
        }
        return tmp;
    }

    //diff of clock wise from x1y1 to x3y3, with x2y2 as the base point
    double getDiff(int x1, int y1, int x2, int y2, int x3, int y3) {
        double angle1 = getAngle(x1, y1, x2, y2);
        double angle2 = getAngle(x3, y3, x2, y2);
        if (angle1 > angle2) {
            return angle1 - angle2;
        }
        if (angle1 < angle2) {
            return 360 - (angle2 - angle1);
        }
        return 0;
    }
public:
    double PI = 3.1415926;
    bool isConvex(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 3) {
            return true;
        }

        int less = 0;
        int more = 0;
        for (int i = 0; i < n; i++) {
            int diff = getDiff(points[(i - 1 + n) % n][0], points[(i - 1 + n) % n][1],
                               points[i][0], points[i][1],
                               points[(i + 1) % n][0], points[(i + 1) % n][1]);

            if (diff < 180) {
                less++;
            }
            else if (diff > 180) {
                more++;
            }
            if (less && more) {
                return false;
            }
        }
        return true;
    }
};
