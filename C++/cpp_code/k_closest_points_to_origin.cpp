/*
973. K Closest Points to Origin
https://leetcode.com/problems/k-closest-points-to-origin/

We have a list of points on the plane.
Find the K closest points to the origin (0, 0).

(Here, the distance between two points on a plane is the Euclidean distance.)

You may return the answer in any order.
The answer is guaranteed to be unique (except for the order that it is in.)

Example 1:
Input: points = [[1,3],[-2,2]], K = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].

Example 2:
Input: points = [[3,3],[5,-1],[-2,4]], K = 2
Output: [[3,3],[-2,4]]
(The answer [[-2,4],[3,3]] would also be accepted.)

Note:
1 <= K <= points.length <= 10000
-10000 < points[i][0] < 10000
-10000 < points[i][1] < 10000
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

class Solution {
public:
    vector<vector<int> > kClosest(vector<vector<int> > &points, int K) {
        vector<pair<int, int> > pts;
        for (int i = 0; i < points.size(); i++) {
            vector<int> &point = points[i];
            pts.push_back({point[0] * point[0] + point[1] * point[1], i});
        }

        sort(pts.begin(), pts.end(), [](pair<int, int> &a, pair<int, int> &b) {
            return a.first < b.first;
        });

        vector<vector<int> > result;
        for (int i = 0; i < K; i++) {
            result.push_back(points[pts[i].second]);
        }
        return result;
    }
};