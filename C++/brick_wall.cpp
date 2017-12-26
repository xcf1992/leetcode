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
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int> edges;
        int crossEdges = 0;

        for (int i = 0; i < wall.size(); i++) {
            int edge = 0;
            for (int j = 0; j < wall[i].size() - 1; j++) {
                edge += wall[i][j];
                edges[edge] += 1;
                crossEdges = max(crossEdges, edges[edge]);
            }
        }

        return wall.size() - crossEdges;
    }
};