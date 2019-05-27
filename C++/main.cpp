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
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<pair<int, int>> stk;
        stk.push_back({0, 0});
        vector<int> result;
        int step = 1;
        while (!stk.empty()) {
            vector<pair<int, int>> next;
            vector<int> cur;
            
            for (int k = 0; k < stk.size(); ++k) {
                int i = stk[k].first;
                int j = stk[k].second;
                cur.push_back(matrix[i][j]);
                
                if (j == 0 and i + 1 < m) {
                    next.push_back({i + 1, j});
                }
                if (j + 1 < n) {
                    next.push_back({i, j + 1});
                }
            }
            stk = next;
            
            int start = step == 1 ? 0 : cur.size() - 1;
            int end = step == 1 ? cur.size() - 1 : 0;
            for (int i = start; i <= end; i += step == 1 ? 1 : -1) {
                result.push_back(cur[i]);
            }
            step = 1 - step;
        }
        return result;
    }
};

int main() {
    int x = stoi("001");
    Solution s;
    vector<int> temp({4,5,6,7,0,1,2});
    vector<vector<int>> matrix({
        {1,2,3},
        {4,5,6},
        {7,8,9}
    });
    s.findDiagonalOrder(matrix);
}
