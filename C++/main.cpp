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
public:
    int maxSumDivThree(vector<int> nums) {
        vector<int> dp({0, INT_MIN, INT_MIN});
        for (int num : nums) {
            vector<int> temp({0, INT_MIN, INT_MIN});
            for (int i = 0; i < 3; ++i) {
                int rem = (i + num) % 3;
                temp[rem] = max(dp[i] + num, dp[rem]);
            }
            dp = temp;
        }
        return dp[0];
    }
};

int main() {
    vector<vector<int>> matrix({{1,1,1,1,1,1,1,0},{1,0,0,0,0,1,1,0},{1,0,1,0,1,1,1,0},{1,0,0,0,0,1,0,1},{1,1,1,1,1,1,1,0}});
    
    Solution s;
    s.maxSumDivThree({1,3,5,7,9});
}
