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
    int minAreaRect(vector<vector<int>> points) {
        unordered_map<int, vector<pair<int, int>>> x2Point;
        unordered_map<int, vector<pair<int, int>>> y2Point;
        for (vector<int>& point : points) {
            x2Point[point[0]].push_back({point[0], point[1]});
            y2Point[point[1]].push_back({point[0], point[1]});
        }
        for (auto it = x2Point.begin(); it != x2Point.end(); it++) {
            sort((it -> second).begin(), (it -> second).end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
                return a.second < b.second;
            });
        }
        for (auto it = y2Point.begin(); it != y2Point.end(); it++) {
            sort((it -> second).begin(), (it -> second).end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
                return a.first < b.first;
            });
        }
        
        int result = INT_MAX;
        for (vector<int>& point : points) {
            int x = point[0];
            int y = point[1];
            if (x2Point[x].size() >= 2 and y2Point[y].size() >= 2) {
                vector<pair<int, int>> xPoints = x2Point[x];
                vector<pair<int, int>> yPoints = y2Point[y];
                
                auto it = lower_bound(yPoints.begin(), yPoints.end(), x, [](pair<int, int>& a, int val) -> bool {
                    return a.first < val;
                });
                int xLength = INT_MAX;
                if (it != yPoints.begin()) {
                    xLength = min(xLength, abs(x - (it - 1) -> first));
                }
                if (it != (yPoints.end() - 1)) {
                    xLength = min(xLength, abs(x - (it + 1) -> first));
                }
                
                it = lower_bound(xPoints.begin(), xPoints.end(), y, [](pair<int, int>& a, int val) -> bool {
                    return a.second < val;
                });
                int yLength = INT_MAX;
                if (it != xPoints.begin()) {
                    yLength = min(yLength, abs(y - (it - 1) -> second));
                }
                if (it != (xPoints.end() - 1)) {
                    yLength = min(yLength, abs(y - (it + 1) -> second));
                }
                
                result = min(result, xLength * yLength);
            }
        }
        return result == INT_MAX ? 0 : result / 2;
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<vector<int>> vb({{3,0}});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({
        {1,1,1,0,1,1,1,1},
        {1,0,0,0,0,1,1,1},
        {1,1,1,0,0,0,1,1},
        {1,1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0}
    });
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    vector<vector<int>> matrix3({
        {1,0},
        {0,1}
    });
    
    s.minAreaRect({{1,1},{1,3},{3,1},{3,3},{2,2}});
    return 0;
}
