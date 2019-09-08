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
#include "extra_data_types.hpp"
using namespace std;

class Solution {
public:
    vector<int> shortestDistanceColor(vector<int> colors, vector<vector<int>> queries) {
        int n = colors.size();
        vector<vector<int>> left(4, vector<int>(n, INT_MAX));
        vector<vector<int>> right(4, vector<int>(n, INT_MAX));
        
        left[colors[0]][0] = 0;
        right[colors[n - 1]][n - 1] = 0;
        for (int i = 1; i < n; ++i) {
            int clr = colors[i];
            left[1][i] = clr == 1 ? 0 : (left[1][i - 1] == INT_MAX ? INT_MAX : left[1][i - 1] + 1);
            left[2][i] = clr == 2 ? 0 : (left[2][i - 1] == INT_MAX ? INT_MAX : left[2][i - 1] + 1);
            left[3][i] = clr == 3 ? 0 : (left[3][i - 1] == INT_MAX ? INT_MAX : left[3][i - 1] + 1);
            
            int j = n - 1 - i;
            clr = colors[j];
            right[1][i] = clr == 1 ? 0 : (right[1][i + 1] == INT_MAX ? INT_MAX : right[1][i + 1] + 1);
            right[2][i] = clr == 2 ? 0 : (right[2][i + 1] == INT_MAX ? INT_MAX : right[2][i + 1] + 1);
            right[3][i] = clr == 3 ? 0 : (right[3][i + 1] == INT_MAX ? INT_MAX : right[3][i + 1] + 1);
        }
        
        int len = queries.size();
        vector<int> result(len, -1);
        for (int i = 0; i < len; ++i) {
            int idx = queries[i][0];
            int clr = queries[i][1];
            result[i] = min(left[clr][idx], right[clr][idx]);
        }
        return result;
    }
};

int main() {
    Solution s;
    s.shortestDistanceColor({1,1,2,1,3,2,2,3,3}, {{1,3}});

    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"hot","dot","dog","lot","log","cog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
}
