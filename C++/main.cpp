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
    int mergeSort(vector<long>& preSum, int lower, int upper, int left, int right) {
        if (left == right - 1) {
            return preSum[left] >= lower and preSum[right] <= upper ? 1 : 0;
        }

        int mid = left + (right - left) / 2;
        int count = mergeSort(preSum, lower, upper, left, mid) + mergeSort(preSum, lower, upper, mid, right);
        for (int i = left; i < mid; ++i) {
            auto m = lower_bound(preSum.begin() + mid, preSum.begin() + right, preSum[i] + lower);
            auto n = upper_bound(preSum.begin() + mid, preSum.begin() + right, preSum[i] + upper);
            count += n - m;
        }
        inplace_merge(preSum.begin() + left, preSum.begin() + mid, preSum.begin() + right);
        return count;
    }
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int len = nums.size();
        vector<long> preSum(len, 0);
        preSum[0] = nums[0];
        for (int i = 1; i < len; ++i) {
            preSum[i] = preSum[i - 1] + nums[i];
        }
        return mergeSort(preSum, lower, upper, 0, len);
    }
};

int main() {
    vector<int> temp({-2,5,-1});
    Solution s;
    s.countRangeSum(temp, -2, 2);

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
}
