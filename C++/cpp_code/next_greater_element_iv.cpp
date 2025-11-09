/*
https://leetcode.com/problems/next-greater-element-iv/description/
2454. Next Greater Element IV

You are given a 0-indexed array of non-negative integers nums. For each integer in nums, you must find its respective
second greater integer.

The second greater integer of nums[i] is nums[j] such that:

j > i
nums[j] > nums[i]
There exists exactly one index k such that nums[k] > nums[i] and i < k < j.
If there is no such nums[j], the second greater integer is considered to be -1.

For example, in the array [1, 2, 4, 3], the second greater integer of 1 is 4, 2 is 3, and that of 3 and 4 is -1.
Return an integer array answer, where answer[i] is the second greater integer of nums[i].



Example 1:

Input: nums = [2,4,0,9,6]
Output: [9,6,6,-1,-1]
Explanation:
0th index: 4 is the first integer greater than 2, and 9 is the second integer greater than 2, to the right of 2.
1st index: 9 is the first, and 6 is the second integer greater than 4, to the right of 4.
2nd index: 9 is the first, and 6 is the second integer greater than 0, to the right of 0.
3rd index: There is no integer greater than 9 to its right, so the second greater integer is considered to be -1.
4th index: There is no integer greater than 6 to its right, so the second greater integer is considered to be -1.
Thus, we return [9,6,6,-1,-1].
Example 2:

Input: nums = [3,3]
Output: [-1,-1]
Explanation:
We return [-1,-1] since neither integer has any integer greater than it.


Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
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
#include <map>
#include <stdio.h>

using namespace std;

class Solution {
public:
    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> rst(n, -1);
        stack<int> min_stk_1; // used to find first next larger element
        stack<int> min_stk_2; // used to find second next larger element
        for (int i = 0; i < n; i++) {
            while (!min_stk_2.empty() && nums[i] > nums[min_stk_2.top()]) {
                rst[min_stk_2.top()] = nums[i];
                min_stk_2.pop();
            }

            stack<int> temp_stk;
            while (!min_stk_1.empty() && nums[i] > nums[min_stk_1.top()]) {
                temp_stk.push(min_stk_1.top());
                min_stk_1.pop();
            }

            while (!temp_stk.empty()) {
                min_stk_2.push(temp_stk.top());
                temp_stk.pop();
            }
            min_stk_1.push(i);
        }
        return rst;
    }
};