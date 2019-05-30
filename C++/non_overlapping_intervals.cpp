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
using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) {
            return 0;
        }

        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1] or (a[1] == b[1] and a[0] < b[0]);
        });

        int result = 1;
        int preEnd = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (preEnd <= intervals[i][0]) {
                result += 1;
                preEnd = intervals[i][1];
            }
        }
        return intervals.size() - result;
    }
};

// dp[i] means how many intervals we can keep from intervals[0] ~ intervals[i], both included
class Solution1 {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n <= 1) {
            return 0;
        }
        
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0] or (a[0] == b[0] and a[1] < b[1]);
        });
        
        vector<int> dp(n, 0);
        dp[0] = 1;
        int result = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (intervals[j][1] <= intervals[i][0]) {
                    dp[i] = max(dp[j] + 1, dp[i]);
                }
            }
            result = max(result, dp[i]);
        }
        return n - result;
    }
};
