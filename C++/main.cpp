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
public:
    bool isRectangleCover(vector<vector<int>> rectangles) {
        int leftX = rectangles[0][0], leftY = rectangles[0][1];
        int rightX = rectangles[0][2], rightY = rectangles[0][3];
        int sum = 0;
        for (int i = 1; i < rectangles.size(); i++) {
            if (rectangles[i][0] <= leftX and rectangles[i][1] <= leftY) {
                leftX = rectangles[i][0];
                leftY = rectangles[i][1];
            }
            if (rectangles[i][2] >= rightX and rectangles[i][3] >= rightY) {
                rightX = rectangles[i][2];
                rightY = rectangles[i][3];
            }
            sum += ((rectangles[i][2] - rectangles[i][0]) * (rectangles[i][3] - rectangles[i][1]));
        }
        return sum == ((rightX - leftX) * (rightY - leftY));
    }
};

int main() {
    Solution s;
    s.isRectangleCover({{1,1,3,3}, {3,1,4,2}, {3,2,4,4}, {1,3,2,4}, {2,3,3,4}});
    return 0;
}
