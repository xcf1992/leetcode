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
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> preSum;
        int sum = 0;
        int result = 0;
        for (int num : nums) {
            sum += num;
            if (preSum.find(sum - k) != preSum.end()) {
                result += sum[sum - k];
            }
            preSum[sum] += 1;
        }
        return result;
    }
};