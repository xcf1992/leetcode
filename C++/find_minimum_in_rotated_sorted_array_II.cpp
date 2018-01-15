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
    int findMin(vector<int>& nums) {
        int start = 0;
        int end = nums.size() - 1;
        while (nums[start] >= nums[end]) {
            int mid = start + (end - start) / 2;
            
            if (nums[mid] == nums[start] && nums[mid] == nums[end]) {
                int result = nums[start];
                for (int i = start + 1; i <= end; i++) {
                    result = min(result, nums[i]);
                }
                return result;
            }
            
            if (nums[mid] >= nums[start]) {
                start = mid + 1;
            }
            else {
                end = mid;
            }
        }
        return nums[start];
    }
};
