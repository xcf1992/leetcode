/*
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=558358&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption%5B3046%5D%5Bvalue%5D%3D37%26searchoption%5B3046%5D%5Btype%5D%3Dradio%26sortid%3D311%26orderby%3Ddateline
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    int maximumStars(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        sort(intervals.begin(), intervals.end(),
             [](vector<int>& a, vector<int>& b) { return a[1] < b[1] or (a[1] == b[1] and a[0] < b[0]); });

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