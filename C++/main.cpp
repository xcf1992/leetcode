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
    int tallestBillboard(vector<int> rods) {
        int n = rods.size();
        int maxLength = 5000; // as the sum could be at most 5000
        vector<vector<int>> dp(n + 1, vector<int>(maxLength + 1));
        for (int diff = 0; diff < maxLength; diff++) {
            dp[0][diff] = INT_MIN;
        }
        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int diff = 0; diff <= maxLength; diff++) {
                dp[i][diff] = dp[i - 1][diff]; // we could choose not to use rods[i - 1]
                if (diff >= rods[i - 1]) { // the order of bag0 and bag1 does not change
                    dp[i][diff] = max(dp[i - 1][diff + rods[i - 1]], dp[i - 1][diff - rods[i - 1]] + rods[i - 1]);
                }
                else {
                    dp[i][diff] = max(dp[i][diff], dp[i - 1][rods[i - 1] - diff] + diff);
                }
            }
        }
        return dp[n][0];
    }
};

int main() {
    Solution s;
    s.tallestBillboard({1,2,3,4,5,6});
    return 0;
}
