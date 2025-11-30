/*
447. Number of Boomerangs
Given n points in the plane that are all pairwise distinct,
a "boomerang" is a tuple of points (i, j, k)
such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Find the number of boomerangs.
You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).

Example:

Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]
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
#include <climits>
using namespace std;

class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int result = 0;
        for (int i = 0; i < points.size(); i++) {
            unordered_map<long, int> distance(points.size());
            for (int j = 0; j < points.size(); j++) {
                if (i == j) {
                    continue;
                }

                int dx = points[i][0] - points[j][0];
                int dy = points[i][1] - points[j][1];
                distance[dx * dx + dy * dy] += 1;
            }

            for (auto& num : distance) {
                result += num.second * (num.second - 1);
            }
        }
        return result;
    }
};