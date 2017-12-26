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
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int result = 0;
        for (int i = nums.size() - 1; i > 1; i--) {
            int j = i - 1;
            int k = 0;
            while (k < j) {
                if (nums[k] + nums[j] > nums[i]) {
                    result += j - k;
                    j -= 1;
                }
                else {
                    k += 1;
                }
            }
        }
        return result;
    }
};