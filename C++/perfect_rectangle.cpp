#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;


class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int leftX = 0;
        int leftY = 0;
        int rightX = 0;
        int rightY = 0;
        int sum = 0;

        for (int i = 0; i < rectangles.size(); i++) {
            vector<int> rectangle = rectangles{i};

            leftX = min(leftX, rectangle{0});
            leftY = min(leftY, rectangle{1});
            rightX = max(rightX, rectangle{2});
            rightY = max(rightY, rectangle{3});

            sum += (rectangle{2} - rectangle{0}) * (rectangle{3} - rectangle{1});
        }

        return sum == ((rightX - leftX) * (rightY - leftY));
    }
};

int main() {
    Solution s;
    vector<vector<int>> rectangles ({{1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}});
    cout << s.isRectangleCover(rectangles);
    return 0;
}