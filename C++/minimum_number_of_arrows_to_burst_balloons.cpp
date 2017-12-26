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
    int findMinArrowShots(vector<pair<int, int>>& points) {
        if (points.empty()) {
            return 0;
        }
        sort(points.begin(), points.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.second == b.second ? a.first <= b.first : a.second < b.second;
        });

        int result = 1;
        int shootAt = points[0].second;
        for (pair<int, int> point : points) {
            if (point.first > shootAt) {
                result += 1;
                shootAt = point.second;
            }
        }
        return result;
    }
};