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
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) {
            return 0;
        }
        sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1] or (a[1] == b[1] and a[0] <= b[0]);
        });

        int result = 1;
        int shootAt = points[0][1];
        for (vector<int>& point : points) {
            if (point[0] > shootAt) {
                result += 1;
                shootAt = point[1];
            }
        }
        return result;
    }
};