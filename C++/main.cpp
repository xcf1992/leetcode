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
    int orderOfLargestPlusSign(int N, vector<vector<int>> mines) {
        vector<vector<int>> grid(N, vector<int>(N, 1));
        for (vector<int>& mine : mines) {
            grid[mine[0]][mine[1]] = 0;
        }

        vector<vector<int>> dp(N, vector<int>(N, N));
        for (int i = 0; i < N; ++i) {
            int left = 0;
            int right = 0;
            int up = 0;
            int down = 0;
            for (int j = 0; j < N; ++j) {
                left = grid[i][j] == 0 ? 0 : left + 1;
                dp[i][j] = min(dp[i][j], left);

                right = grid[i][N - 1 - j] == 0 ? 0 : right + 1;
                dp[i][j] = min(dp[i][N - 1 - j], right);

                up = grid[j][i] == 0 ? 0 : up + 1;
                dp[j][i] = min(dp[j][i], up);

                down = grid[j][N - 1 - i] == 0 ? 0 : down + 1;
                dp[j][N - 1 - i] = min(dp[j][N - 1 - i], down);
            }
        }

        int result = 0;
        for (vector<int>& row : dp) {
            for (int count : row) {
                result = max(result, count);
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({0,1,3,50,75});
    vector<vector<int>> matrix({{8,2},{4,2},{4,5},{2,0},{7,2},{1,4},{9,1},{3,1},{9,0},{1,0}});
    s.orderOfLargestPlusSign(5, {{4,2}});
}
