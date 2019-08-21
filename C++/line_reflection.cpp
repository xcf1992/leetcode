/*
356. Line Reflection
Given n points on a 2D plane, find if there is such a line parallel to y-axis that reflect the given points.

Example 1:

Input: [[1,1],[-1,1]]
Output: true
Example 2:

Input: [[1,1],[-1,-1]]
Output: false
Follow up:
Could you do better than O(n2) ?
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

class Solution {
public:
    bool isReflected(vector<vector<int>>& points) {
        int xMin = INT_MAX;
        int xMax = INT_MIN;
        unordered_map<int, unordered_set<int>> memo;
        for (vector<int>& point : points) {
            xMin = min(xMin, point[0]);
            xMax = max(xMax, point[0]);
            memo[point[0]].insert(point[1]);
        }

        int sum = xMax + xMin;
        for (vector<int>& point : points) {
            int target = sum - point[0];
            if (memo.find(target) == memo.end() or memo[target].find(point[1]) == memo[target].end()) {
                return false;
            }
        }
        return true;
    }
};

class Solution {
public:
    bool isReflected(vector<pair<int, int>>& points) {
        if (points.size() <= 1) {
            return true;
        }

        sort(points.begin(), points.end());

        int mid = points.front().first + points.back().first;
        int xXor = 0;
        int yXor = 0;
        for (int i = 0; i < points.size(); i++) {
            if (i != 0 && points[i].first == points[i - 1].first) {
                continue;
            }

            if (2 * points[i].first != mid) {
                yXor ^= points[i].second;
                xXor ^= (abs(mid - 2 * points[i].first));
            }
        }
        return xXor == 0 && yXor == 0;
    }
};
