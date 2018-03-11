/*
 Given a sorted array of integers nums and integer values a, b and c. Apply a quadratic function of the form f(x) = ax2 + bx + c to each element x in the array.
 
 The returned array must be in sorted order.
 
 Expected time complexity: O(n)
 
 Example:
 nums = [-4, -2, 2, 4], a = 1, b = 3, c = 5,
 
 Result: [3, 9, 15, 33]
 
 nums = [-4, -2, 2, 4], a = -1, b = 3, c = 5
 
 Result: [-23, -5, 1, 7]
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
#include <stdio.h>
using namespace std;

class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        vector<int> result;
        if (a == 0) {
            for (int i : nums) {
                result.push_back(b * i + c);
            }
            if (b >= 0) {
                return result;
            }
            else {
                reverse(result.begin(), result.end());
                return result;
            }
        }
        int n = nums.size();
        double mid = 0 - (double)b / (2 * a);
        int left = 0;
        int right = n - 1;
        while (left < n - 1 && ((double)nums[left + 1]) < mid) {
            left += 1;
        }
        while (right > 0 && ((double)nums[right - 1]) >= mid) {
            right -= 1;
        }
        
        while (left >= 0 && right < n) {
            double rightVal = nums[right];
            double leftVal = nums[left];
            if (abs(rightVal - mid) > abs(leftVal - mid)) {
                result.push_back(a * nums[left] * nums[left] + b * nums[left] + c);
                left -= 1;
            }
            else {
                result.push_back(a * nums[right] * nums[right] + b * nums[right] + c);
                right += 1;
            }
        }
        
        while (left >= 0) {
            result.push_back(a * nums[left] * nums[left] + b * nums[left] + c);
            left -= 1;
        }
        while (right < n) {
            result.push_back(a * nums[right] * nums[right] + b * nums[right] + c);
            right += 1;
        }
        if (a < 0) {
            reverse(result.begin(), result.end());
        }
        return result;
    }
};
