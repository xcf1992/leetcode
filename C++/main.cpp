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
    int mod = 1e9 + 7;
public:
    int profitableSchemes(int G, int P, vector<int> group, vector<int> profit) {
        int n = group.size();
        vector<vector<int>> dp(P + 1, vector<int>(G + 1, 0));
        // when there is 0 crime, 0 scheme existed for any profit > 0 or group > 0
        dp[0][0] = 1;
        for (int i = 0; i < n; ++i) {
            int p = profit[i];
            int g = group[i];
            for (int j = P; j >= 0; j--) {
                for (int k = G; k >= g; k--) {
                    dp[j][k] += dp[max(0, j - p)][k - g];
                    dp[j][k] %= mod;
                }
            }
        }
        
        long result = 0;
        for (int i = 0; i <= G; i++) {
            result += dp[P][i];
            result %= mod;
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,17,8});
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
    s.profitableSchemes(5, 3, {2,2}, {2,3});
}
