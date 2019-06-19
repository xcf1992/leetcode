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
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>> points) {
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
                if (points[i][0] == points[j][0] && points[i][1] == points[j][1]) {
                    same++;
                    continue;
                }
                if (points[i][0] == points[j][0]) {
                    vertical++;
                    continue;
                }
                slope = (double) (points[i][1] - points[j][1]) / (points[i][0] - points[j][0]);
                count[slope] += 1;
            }
            result = max(result, vertical + same);
            for (auto it = count.begin(); it != count.end(); it++) {
                result = max(result, it -> second + same);
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({5,4,3,2,1});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<char>> matrix({
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    });
    s.maxPoints({{0,0}, {94911151,94911150}, {94911152,94911151}});
}
