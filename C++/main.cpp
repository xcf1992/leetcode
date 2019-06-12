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
    int validSubarrays(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return n;
        }

        int result = 0;
        stack<pair<int, int>> stk;
        for (int i = n - 1; i >= 0; --i) {
            if (!stk.empty() and nums[i] < stk.top().second) {
                stk.pop();
            }
            result += (stk.empty() ? n : stk.top().first) - i;
            stk.push({i, nums[i]});
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,4,2,5,3});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    s.validSubarrays(temp);
}
