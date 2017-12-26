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
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int result = 0;
        for (int i = 0; i < points.size(); i++) {
            unordered_map<long, int> distance(points.size());
            for (int j = 0; j < points.size(); j++) {
                if (i == j) {
                    continue;
                }

                int dx = points[i].first - points[j].first;
                int dy = points[i].second - points[j].second;

                distance[dx * dx + dy * dy] += 1;
            }

            for (auto num : distance) {
                result += num.second * (num.second - 1);
            }
        }

        return result;
    }
};