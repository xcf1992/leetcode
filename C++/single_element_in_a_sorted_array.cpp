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
    int singleNonDuplicate(vector<int>& nums) {
        int start = 0;
        int end = nums.size() - 1;
        while (start < end) {
            int mid = start + (end - start) / 2;
            int num = nums[mid];

            if (mid < end && num == nums[mid + 1]) {
                if ((end - mid + 1) % 2 == 0) {
                    end = mid - 1;
                }
                else {
                    start = mid;
                }
            }
            else if (mid > start && num == nums[mid - 1]) {
                if ((end - mid) % 2 == 0) {
                    end = mid;
                }
                else {
                    start = mid + 1;
                }
            } else {
                return num;
            }
        }
        return nums[start];
    }
};