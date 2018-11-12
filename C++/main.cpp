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
        map<int, vector<int>> x2Points;
        for (vector<int>& point : points) {
            x2Points[point[0]].push_back(point[1]);
        }
        
        int result = INT_MAX;
        unordered_map<int, int> memo;
        for (auto it = x2Points.begin(); it != x2Points.end(); it++) {
            int x = it -> first;
            vector<int> yPoints = it -> second;
            sort(yPoints.begin(), yPoints.end());
            for (int i = 0; i < yPoints.size() - 1; i++) {
                int y1 = yPoints[i];
                int y2 = yPoints[i + 1];
                int code = 40001 * y1 + y2;
                if (memo.find(code) != memo.end()) {
                    result = min(result, abs((memo[code] - x) * (y1 - y2)));
                }
                memo[code] = x;
            }
        }
        return result == INT_MAX ? 0 : result;
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
    
    s.minAreaRect({{1,3},{2,1},{2,0},{4,3},{0,4},{4,2},{1,0},{3,4},{2,4},{4,0}});
    return 0;
}
