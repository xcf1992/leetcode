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
    int numSubarrayProductLessThanK(vector<int> nums, int k) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }
        vector<double> preSum(n + 1, 0.0);
        for (int i = 0; i <= n; ++i) {
            preSum[i + 1] = preSum[i] + log10(nums[i]);
        }

        int result = 0;
        for (int i = 0; i <= n; ++i) {
            double target = preSum[i] + log10(k);
            auto it = lower_bound(preSum.begin(), preSum.end(), target, [&](double a, double b) {
                return a < b;
            });
            int index = (it - preSum.begin()) - 1;
            if (index >= i) {
                result += index - i;
            }
        }
        return result;
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
    s.numSubarrayProductLessThanK({10,5,2,6}, 100);
}
