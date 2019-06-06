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
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        int n = A.size();
        if (n == 0) {
            return 0;
        }

        vector<vector<int>> dp(K + 1, vector<int>(n, 0));
        int curMax = INT_MIN;
        for (int i = 0; i < n; i++) {
            curMax = max(curMax, A[i]);
            dp[1][i] = curMax;
        }

        int result = dp[1][n - 1];
        for (int k = 2; k <= K; ++k) {
            for (int i = k - 1; i < n; ++i) {
                curMax = A[i];
                for (int j = i; j >= k - 1; j--) {
                    curMax = max(curMax, A[j]);
                    dp[k][i] = max(dp[k][i], dp[k - 1][j - 1] + (i - j + 1) * curMax);
                }
            }
            result = max(result, dp[k][n - 1]);
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,15,7,9,2,5,10});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    s.maxSumAfterPartitioning(temp, 3);
}
