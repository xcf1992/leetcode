/*
1453. Maximum Number of Darts Inside of a Circular Dartboard
https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/

You have a very large square wall and a circular dartboard placed on the wall.
You have been challenged to throw darts into the board blindfolded.
Darts thrown at the wall are represented as an array of points on a 2D plane.

Return the maximum number of points that are within or lie on any circular dartboard of radius r.

Example 1:
Input: points = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
Output: 4
Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.

Example 2:
Input: points = [[-3,0],[3,0],[2,6],[5,4],[0,9],[7,8]], r = 5
Output: 5
Explanation: Circle dartboard with center in (0,4) and radius = 5 contain all points except the point (7,8).

Example 3:
Input: points = [[-2,0],[2,0],[0,2],[0,-2]], r = 1
Output: 1

Example 4:
Input: points = [[1,2],[3,5],[1,-1],[2,3],[4,1],[1,3]], r = 2
Output: 4

Constraints:
1 <= points.length <= 100
points[i].length == 2
-10^4 <= points[i][0], points[i][1] <= 10^4
1 <= r <= 5000
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
#include <cfloat>
#include <stdio.h>
#include <map>
using namespace std;
/*
Reference
POJ: http://poj.org/problem?id=1981
StackOverflow:
https://stackoverflow.com/questions/3229459/algorithm-to-cover-maximal-number-of-points-with-one-circle-of-given-radius/3229582#3229582


Plan
Well, I doubt if this problem is appropriate for Leetcode or interview.

If you meet this prolem during interview,
you can ask the interviewer:
"Could you give me some APIs?"


Explanation
The basic idea is that,
imagine that we are shrink the final circle,
until there are at least 2 points on the circle.

We can enumerate all possible circles based on the given points.


Solution 1: O(N^4) brute force
Enumerate all combinations of 3 points,
find the circumcenter of these 3 points.

Use this circumcenter as the center of circle,
and count how many points inside.

If the final result >=3, we won't miss it during this search.
But if we still have res = 1
we still need to check each two pair distance,
to find out if res can be 2.

Time O(N^4)
Space O(1)


Solution 2:
Enumerate all combinations of 2 points,
find the circle going through them with radius = r.

Use this circumcenter as the center of circle,
and count how many points inside.

Also explained by Alexandre C:
Basic observations :

I assume the radius is one,
since it doesn't change anything.
given any two points,
there exists at most two unit circles on which they lie.
given a solution circle to your problem,
you can move it until it contains two points of your set
while keeping the same number of points of your set inside it.
The algorithm is then:

For each pair of points,
if their distance is < 2,
compute the two unit circles C1 and C2 that pass through them.
Compute the number of points of your set inside C1 and C2
Take the max.
Time O(N^3)
Space O(1)
*/
class Solution {
public:
    int numPoints(vector<vector<int>>& points, int r) {
        int res = 1;

        for (int i = 0; i < points.size() - 1; i++) {
            for (int j = i + 1; j < points.size(); j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                double d = (pow(x1 - x2, 2) + pow(y1 - y2, 2)) / 4.0;

                if (d > r * r) {
                    continue;
                }

                double x0 = (x1 + x2) / 2.0 + (y2 - y1) * pow((r * r - d), 0.5) / pow((d * 4), 0.5);
                double y0 = (y1 + y2) / 2.0 - (x2 - x1) * pow((r * r - d), 0.5) / pow((d * 4), 0.5);

                int cnt = 0;

                for (vector<int>& point : points) {
                    double x = point[0];
                    double y = point[1];
                    if (pow((x - x0), 2) + pow((y - y0), 2) <= (double)(r * r) + 0.00001) {
                        cnt++;
                    }
                }

                res = max(res, cnt);

                x0 = (x1 + x2) / 2.0 - (y2 - y1) * pow((r * r - d), 0.5);
                y0 = (y1 + y2) / 2.0 + (x2 - x1) * pow((r * r - d), 0.5);

                cnt = 0;

                for (vector<int>& point : points) {
                    double x = point[0];
                    double y = point[1];
                    if (pow((x - x0), 2) + pow((y - y0), 2) <= (double)(r * r) + 0.00001) {
                        cnt++;
                    }
                }

                res = max(res, cnt);
            }
        }

        return res;
    }
};
