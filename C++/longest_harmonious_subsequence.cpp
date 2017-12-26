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
    int findLHS(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int minVal = nums[0];
        int maxVal = nums[0];
        int minPos = 0;
        int maxPos = 0;
        int result = 0;
        nums.push_back(INT_MAX);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == minVal + 1) {
                if (minVal == maxVal) {
                    maxVal = nums[i];
                    maxPos = i;
                }
            }
            else {
                if (minVal == maxVal) {
                    minPos = i;
                    maxPos = i;
                    minVal = nums[i];
                    maxVal = nums[i];
                }
                else {
                    result = max(result, i - minPos);
                    minVal = maxVal;
                    minPos = maxPos;
                    i--;
                }
            }
        }
        return result;
    }
};