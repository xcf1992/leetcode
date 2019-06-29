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
using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int lenS = s.size();
        int lenT = t.size();
        if (lenS <= 0 or lenT <= 0 or lenS < lenT) {
            return 0;
        }
        
        vector<vector<long>> dp(lenS + 1, vector<long>(lenT + 1, 0));
        for (int i = 0; i <= lenS; ++i) {
            dp[i][0] = 1;
        }
        
        for (int i = 1; i <= lenS; ++i) {
            for (int j = 1; j <= i; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }
        return dp[lenS][lenT];
    }
};

int main() {
    Solution s;
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
        {1,0},
        {0,0}
    });
    vector<string> words({"cat","cats","and","sand","dog"});
    s.numDistinct("rabbbit","rabbit");
}
