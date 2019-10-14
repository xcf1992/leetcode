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
    int maximumStars(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1] or (a[1] == b[1] and a[0] < b[0]);
        });

        int n = intervals.back()[1];
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1];
            for (int k = 0; k < intervals.size(); ++k) {
                int start = intervals[k][0];
                int end = intervals[k][1];
                int stars = intervals[k][2];
                if (end > i) {
                    break;
                }

                dp[i] = max(dp[i], dp[start] + stars);
            }
        }
        return dp[n];
    }
};

int main() {
    Solution s;
    vector<int> temp1({1,2,3});
    vector<vector<int>> matrix({{2, 4, 5}, {3, 5, 6}, {5, 7, 10}, { 4, 8, 12}, {6, 8 ,10}, {10, 12, 4}});
    s.maximumStars(matrix);

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
