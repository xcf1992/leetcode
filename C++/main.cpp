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
private:
    int n = 0;
    int getMaxStone(vector<vector<int>>& dp, vector<int>& preSum, int start, int M) {
        if (start >= n) {
            return 0;
        }

        int total = preSum[n] - preSum[start];
        if (start + 2 * M >= n) {
            return total;
        }

        if (dp[start][M] != INT_MIN) {
            return dp[start][M];
        }

        for (int x = M; x < 2 * M; ++x) {
            dp[start][M] = max(dp[start][M], total - getMaxStone(dp, preSum, start + x, max(M, x)));
        }
        return dp[start][M];
    }
public:
    int stoneGameII(vector<int>& piles) {
        n = piles.size();
        if (n == 0) {
            return 0;
        }

        vector<int> preSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            preSum[i + 1] = piles[i] + preSum[i];
        }

        /*
         * dp[i][j]
         * the max stones the first player can get
         * start with stone[i] (0-based), and with M = j
         */
        vector<vector<int>> dp(n, vector<int>(2 * n, INT_MIN));
        return getMaxStone(dp, preSum, 0, 1);
    }
};

int main() {
    Solution s;
    vector<int> temp({2,7,9,4,4});
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
    s.stoneGameII(temp);
}
