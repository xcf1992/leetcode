/*
 You have a list of points in the plane. Return the area of the largest triangle that can be formed by any 3 of the points.
 
 Example:
 Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
 Output: 2
 Explanation:
 The five points are show in the figure below. The red triangle is the largest.
 
 
 Notes:
 
 3 <= points.length <= 50.
 No points will be duplicated.
 -50 <= points[i][j] <= 50.
 Answers within 10^-6 of the true value will be accepted as correct.
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
private:
    double calculate(vector<int>& a, vector<int>& b, vector<int>& c) {
        return a[0] * b[1] + b[0] * c[1] + c[0] * a[1] - b[0] * a[1] - c[0] * b[1] - a[0] * c[1];
    }
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        double result = 0.0;
        for (vector<int>& a : points) {
            for (vector<int>& b : points) {
                for (vector<int>& c : points) {
                    result = max(result, abs(calculate(a, b, c)) * 0.5);
                }
            }
        }
        return result;
    }
};
