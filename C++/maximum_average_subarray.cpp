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
    double findMaxAverage(vector<int>& nums, int k) {
        double curSum = 0.0;
        for (int i = 0; i < k; i++) {
            curSum += nums[i];
        }

        int start = 0;
        int end = k;
        double maxSum = curSum;
        while (end < nums.size()) {
            curSum = maxSum - nums[start] + nums[end];
            maxSum = max(maxSum, curSum);
            start += 1;
            end += 1;
        }
        return maxSum / k;
    }
};