/*
https://leetcode.com/problems/max-points-on-a-line/description/
149. Max Points on a Line
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

Example 1:

Input: [[1,1],[2,2],[3,3]]
Output: 3
Explanation:
^
|
|        o
|     o
|  o
+------------->
0  1  2  3  4
Example 2:

Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6
NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method
signature.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2) {
            return n;
        }

        int rst = 0;
        for (int i = 0; i < n; i++) {
            int same = 1;
            int vertical = 0;
            unordered_map<string, int> cnt;
            for (int j = i + 1; j < n; j++) {
                if (points[i][0] == points[j][0] && points[i][1] == points[j][1]) {
                    same += 1;
                    continue;
                }

                if (points[i][0] == points[j][0]) {
                    vertical += 1;
                    continue;
                }

                int dx = points[i][0] - points[j][0];
                int dy = points[i][1] - points[j][1];
                int gcd_val = std::gcd(abs(dx), abs(dy));
                if (dx < 0) {
                    dx = -dx;
                    dy = -dy;
                }
                string key = to_string(dx / gcd_val) + "_" + to_string(dy / gcd_val);
                cnt[key] += 1;
            }

            rst = max(rst, same + vertical);
            for (auto& [key, val] : cnt) {
                rst = max(rst, same + val);
            }
        }
        return rst;
    }
};

/*
wrong answer [[0,0],[94911151,94911150],[94911152,94911151]]
cause two points are too close, thus the slope cannot be differentiated under c++ double
*/
class Solution1 {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2) {
            return n;
        }

        int result = 0;
        for (int i = 0; i != n; i++) {
            int same = 1;
            int vertical = 0;
            unordered_map<double, int> count;

            for (int j = i + 1; j < n; j++) {
                double slope = 0.0;
                if (points[i][0] == points[j][0] and points[i][1] == points[j][1]) {
                    same++;
                    continue;
                }
                if (points[i][0] == points[j][0]) {
                    vertical++;
                    continue;
                }
                slope = (double)(points[i][1] - points[j][1]) / (points[i][0] - points[j][0]);
                count[slope] += 1;
            }
            result = max(result, vertical + same);
            for (auto it = count.begin(); it != count.end(); it++) {
                result = max(result, it->second + same);
            }
        }
        return result;
    }
};