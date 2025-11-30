/*
1785. Minimum Elements to Add to Form a Given Sum
https://leetcode.com/problems/minimum-elements-to-add-to-form-a-given-sum/

You are given an integer array nums and two integers limit and goal.
The array nums has an interesting property that abs(nums[i]) <= limit.

Return the minimum number of elements you need to add to make the sum of the array equal to goal.
The array must maintain its property that abs(nums[i]) <= limit.

Note that abs(x) equals x if x >= 0, and -x otherwise.

Example 1:
Input: nums = [1,-1,1], limit = 3, goal = -4
Output: 2
Explanation: You can add -2 and -3, then the sum of the array will be 1 - 1 + 1 - 2 - 3 = -4.
Example 2:
Input: nums = [1,-10,9,1], limit = 100, goal = 0
Output: 1

Constraints:
1 <= nums.length <= 105
1 <= limit <= 106
-limit <= nums[i] <= limit
-109 <= goal <= 109
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
using namespace std;

class Solution {
public:
    int minElements(vector<int>& A, int limit, int goal) {
        long sum = accumulate(A.begin(), A.end(), 0L), diff = abs(goal - sum);
        return (diff + limit - 1) / limit;
    }
};
