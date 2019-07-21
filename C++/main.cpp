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

class Solution1 {
private:
    vector<int> count(string num) {
        vector<int> result(2, 0);
        for (char c : num) {
            result[c - '0'] += 1;
        }
        return result;
    }
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (string str : strs) {
                    vector<int> digit = count(str);
                    if (i >= digit[0] and j >= digit[1]) {
                        dp[i][j] = max(dp[i][j], 1 + dp[i - digit[0]][j - digit[1]]);
                    }
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    Solution1 s;
    vector<int> temp({1,3,2,4});
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
    s.findMaxForm(words, 5, 3);
}
