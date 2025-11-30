/*
 665. Non-decreasing Array
 Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.

 We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).

 Example 1:
 Input: [4,2,3]
 Output: True
 Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
 Example 2:
 Input: [4,2,1]
 Output: False
 Explanation: You can't get a non-decreasing array by modify at most one element.
 Note: The n belongs to [1, 10,000].
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class Solution {
private:
    bool nondreasing(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i - 1]) {
                return false;
            }
        }
        return true;
    }

public:
    bool checkPossibility(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++)
            if (nums[i] < nums[i - 1]) {
                int temp = nums[i - 1];
                nums[i - 1] = i - 2 >= 0 ? nums[i - 2] : nums[i];
                if (nondreasing(nums)) {
                    return true;
                }

                nums[i - 1] = temp;
                nums[i] = i + 1 < nums.size() ? nums[i + 1] : nums[i - 1];
                if (nondreasing(nums)) {
                    return true;
                }
                return false;
            }
        return true;
    }
};