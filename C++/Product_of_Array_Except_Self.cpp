#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result(nums.size(), 1);
        for (int i = nums.size() - 2; i >= 0; i--) {
            result[i] = result[i + 1] * nums[i + 1];
        }

        int product = nums[0];
        for (int i = 1;i < result.size(); i++) {
            result[i] = product * result[i];
            product *= nums[i];
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}