/*
 1037. Valid Boomerang

 A boomerang is a set of 3 points that are all distinct and not in a straight line.

 Given a list of three points in the plane, return whether these points are a boomerang.



 Example 1:

 Input: [[1,1],[2,3],[3,2]]
 Output: true
 Example 2:

 Input: [[1,1],[2,2],[3,3]]
 Output: false


 Note:

 points.length == 3
 points[i].length == 2
 0 <= points[i][j] <= 100
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
    bool isBoomerang(vector<vector<int>>& points) {
        vector<int> p1 = points[0];
        vector<int> p2 = points[1];
        vector<int> p3 = points[2];
        return (p2[1] - p1[1]) * (p3[0] - p2[0]) == (p3[1] - p2[1]) * (p2[0] - p1[0]);
    }
};
