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
    string minWindow(string S, string T) {
        int m = S.size();
        int n = T.size();
        int start = -1;
        int minLen = S.size();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= min(i, n); ++j) {
                if (S[i - 1] == T[j - i]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = dp[i - 1][j];
                }
                if (dp[i][n] != -1) {
                    int len = i - dp[i][n];
                    if (minLen > len) {
                        minLen = len;
                        start = dp[i][n];
                    }
                }
            }
        }
        
        return start != -1 ? S.substr(start, minLen) : "";
    }
};

int main() {
    Solution s;
    s.minWindow("cnhczmccqouqadqtmjjzl",
                "mm");
    return 0;
}
