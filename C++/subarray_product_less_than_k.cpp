/*
 Your are given an array of positive integers nums.
 
 Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.
 
 Example 1:
 Input: nums = [10, 5, 2, 6], k = 100
 Output: 8
 Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
 Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
 Note:
 
 0 < nums.length <= 50000.
 0 < nums[i] < 1000.
 0 <= k < 10^6.
 */

#include <iostream>
#include <sstream>
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
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (nums.empty()) {
            return 0;
        }
        
        int start = 0;
        int result = 0;
        int product = 1;
        for (int end = 0; end < nums.size(); end++) {
            product *= nums[end];
            while (start <= end && product >= k) {
                product /= nums[start++];
            }
            result += end - start + 1;
        }
        return result;
    }
};
