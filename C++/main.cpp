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

class Solution { // dp
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> maximum(n, vector<int>(n, INT_MIN));
        for (int i = 0; i < n; ++i) {
            maximum[i][i] = arr[i];
            for (int j = i + 1; j < n; ++j) {
                maximum[i][j] = max(maximum[i][j - 1], arr[j]);
            }
        }

        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = arr[i];
            if (i > 0) {
                dp[i - 1][i] = arr[i - 1] * arr[i];
            }
        }

        for (int count = 3; count <= n; count++) {
            for (int i = 0; i + count - 1 < n; ++i) {
                int j = i + count - 1;
                for (int k = i; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + maximum[i][k] * maximum[k + 1][j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};

int main() {
    Solution s;
    vector<int> temp({6,2,4});
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
    vector<string> words({"10","0001","111001","1","0"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
    s.mctFromLeafValues(temp);
}
