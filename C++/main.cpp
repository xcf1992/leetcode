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
    int rectangleArea(vector<vector<int>> rectangles) {
        int mod = 1e9 + 7;
        unordered_set<int> xValues;
        xValues.insert(0);
        for (vector<int>& rec : rectangles) {
            xValues.insert(rec[0]);
            xValues.insert(rec[2]);
        }
        
        vector<int> x(xValues.begin(), xValues.end());
        sort(x.begin(), x.end());
        unordered_map<int, int> x_i;
        for (int i = 0; i < x.size(); i++) {
            x_i[x[i]] = i;
        }
        
        vector<int> count(x.size(), 0);
        vector<vector<int>> line;
        for (vector<int>& rec : rectangles) {
            int x1 = rec[0], y1 = rec[1], x2 = rec[2], y2 = rec[3];
            // first event to add active x points
            line.push_back({y1, x1, x2, 1});
            // second event to remove inactive x points
            line.push_back({y2, x1, x2, -1});
        }
        sort(line.begin(), line.end());
        
        long long cur_y = 0, cur_x_sum = 0, result = 0;
        for (vector<int>& l : line) {
            long long y = l[0], x1 = l[1], x2 = l[2], sig = l[3];
            result = (result + (y - cur_y) * cur_x_sum) % mod;
            cur_y = y;
            
            for (int i = x_i[x1]; i < x_i[x2]; i++) {
                count[i] += sig;
            }
            cur_x_sum = 0;
            for (int i = 0; i < x.size(); i++) {
                if (count[i] > 0) {
                    cur_x_sum += x[i + 1] - x[i];
                }
            }
        }
        return result;
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
    
    s.rectangleArea({{0,0,2,2}, {1,0,2,3}, {1,0,4,1}});
    return 0;
}
