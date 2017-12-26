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
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, int> points;
        int index = 0;
        for (auto e : equations) {
            if (points.find(e.first) == points.end()) {
                points[e.first] = index;
                index += 1;
            }
            if (points.find(e.second) == points.end()) {
                points[e.second] = index;
                index += 1;
            }
        }

        vector<vector <double>> graph(points.size(), vector<double>(points.size(), INT_MAX));
        for (int i = 0; i < equations.size(); i++) {
            int x = points[equations[i].first];
            int y = points[equations[i].second];
            graph[x][x] = 1.0;
            graph[y][y] = 1.0;
            graph[x][y] = values[i];
            graph[y][x] = 1.0 / values[i];
        }

        for (int k = 0; k < points.size(); k++) {
            for (int i = 0; i < points.size(); i++) {
                for (int j = 0; j < points.size(); j++) {
                    if (graph[i][k] != INT_MAX && graph[k][j] != INT_MAX) {
                        graph[i][j] = min(graph[i][j], graph[i][k] * graph[k][j]);
                    }
                }
            }
        }

        vector<double> result;
        for (auto q : queries) {
            if (points.find(q.first) == points.end() || points.find(q.second) == points.end()) {
                result.push_back(-1.0);
            }
            else {
                result.push_back(graph[points[q.first]][points[q.second]] == INT_MAX ? -1.0 : graph[points[q.first]][points[q.second]]);
            }
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}