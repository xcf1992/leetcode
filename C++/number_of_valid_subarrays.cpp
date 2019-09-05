/*
1063. Number of Valid Subarrays
Given an array A of integers, return the number of non-empty continuous subarrays that satisfy the following condition:

The leftmost element of the subarray is not larger than other elements in the subarray.

Example 1:

Input: [1,4,2,5,3]
Output: 11
Explanation: There are 11 valid subarrays: [1],[4],[2],[5],[3],[1,4],[2,5],[1,4,2],[2,5,3],[1,4,2,5],[1,4,2,5,3].
Example 2:

Input: [3,2,1]
Output: 3
Explanation: The 3 valid subarrays are: [3],[2],[1].
Example 3:

Input: [2,2,2]
Output: 6
Explanation: There are 6 valid subarrays: [2],[2],[2],[2,2],[2,2],[2,2,2].


Note:

1 <= A.length <= 50000
0 <= A[i] <= 100000
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
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    int validSubarrays(vector<int>& nums) {
        int n = nums.size();
        int result = 0;
        stack<pair<int, int>> stk;
        for (int i = n - 1; i >= 0; --i) {
            while (!stk.empty() and nums[i] <= stk.top().second) {
                stk.pop();
            }
            result += (stk.empty() ? n : stk.top().first) - i;
            stk.push({i, nums[i]});
        }
        return result;
    }
};
