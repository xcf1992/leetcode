/*
1748. Sum of Unique Elements
https://leetcode.com/problems/sum-of-unique-elements/

You are given an integer array nums.
The unique elements of an array are the elements that appear exactly once in the array.

Return the sum of all the unique elements of nums.

Example 1:
Input: nums = [1,2,3,2]
Output: 4
Explanation: The unique elements are [1,3], and the sum is 4.
Example 2:
Input: nums = [1,1,1,1,1]
Output: 0
Explanation: There are no unique elements, and the sum is 0.
Example 3:
Input: nums = [1,2,3,4,5]
Output: 15
Explanation: The unique elements are [1,2,3,4,5], and the sum is 15.

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 100
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
#include <numeric>
#include <bitset>
using namespace std;

class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        vector<int> count(101, 0);
        int result = 0;
        for (int num : nums) {
            count[num] += 1;
            if (count[num] == 1) {
                result += num;
            }
            if (count[num] == 2) {
                result -= num;
            }
        }
        return result;
    }
};