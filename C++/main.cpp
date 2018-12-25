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
private:
    double getDistance(int p1, int p2, vector<vector<int>>& points) {
        double distance = pow(points[p1][0] - points[p2][0], 2) + pow(points[p1][1] - points[p2][1], 2);
        return sqrt(distance);
    }
public:
    double minAreaFreeRect(vector<vector<int>> points) {
        int n = points.size();
        unordered_map<string, vector<pair<int, int>>> memo;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double centerX = points[i][0] + points[j][0];
                double centerY = points[i][1] + points[j][1];
                double radius = getDistance(i, j, points);
                string key = to_string(centerX) + "_" + to_string(centerY) + "_" + to_string(radius);
                memo[key].push_back({i, j});
            }
        }

        double result = 0.0;
        for (auto it = memo.begin(); it != memo.end(); it++) {
            vector<pair<int, int>> pList = it -> second;
            int len = pList.size();
            for (int i = 0; i < len; i++) {
                for (int j = i + 1; j < len; j++) {
                    int p1 = pList[i].first;
                    int p2 = pList[i].second;
                    int p3 = pList[j].first;
                    double area = getDistance(p1, p3, points) * getDistance(p2, p3, points);
                    result = max(result, area);
                }
            }
        }
        return result;
    }
};


int main() {
    Solution s;
    s.minAreaFreeRect({{3,1},{1,1},{0,1},{2,1},{3,3},{3,2},{0,2},{2,3}});
    return 0;
}
