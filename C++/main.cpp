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
    int dfs(int workers, int bCount, vector<int>& blocks, int split, vector<vector<int>>& dp) {
        if (bCount <= 0) {
            return 0;
        }

        if (workers <= 0) {
            return INT_MAX;
        }

        if (workers >= bCount) {
            return blocks[bCount - 1];
        }

        if (dp[bCount][workers] != INT_MAX) {
            return dp[bCount][workers];
        }

        int option1 = max(split, blocks[bCount - 1]);
        int rest = INT_MAX;
        for (int i = 1; i <= workers - 1; ++i) {
            rest = min(rest, dfs(workers - i, bCount - i, blocks, split, dp));
        }
        option1 = rest == INT_MAX ? INT_MAX : rest + option1;
        int option2 = split + dfs(workers * 2, bCount, blocks, split, dp);
        dp[bCount][workers] = min(option1, option2);
        return dp[bCount][workers];
    }
public:
    int minBuildTime(vector<int>& blocks, int split) {
        int n = blocks.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
        sort(blocks.begin(), blocks.end());
        return dfs(1, n, blocks, split, dp);
    }
};

int main() {
    vector<int> temp1({1,2,3});
    Solution s;
    s.minBuildTime(temp1, 1);

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
