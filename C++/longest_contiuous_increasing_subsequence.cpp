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
    int findLengthOfLCIS(vector<int>& nums) {
        int current = 1;
        int result = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                current += 1;
            }
            else {
                current = 1;
            }
            result = max(result, current);
        }
        return result;
    }
};