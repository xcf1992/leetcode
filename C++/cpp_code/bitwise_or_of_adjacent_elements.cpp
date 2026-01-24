/*
https://leetcode.com/problems/bitwise-or-of-adjacent-elements/description/
3173. Bitwise OR of Adjacent Elements

Given an array nums of length n, return an array answer of length n - 1 such that answer[i] = nums[i] | nums[i + 1]
where | is the bitwise OR operation.



Example 1:

Input: nums = [1,3,7,15]

Output: [3,7,15]

Example 2:

Input: nums = [8,4,2]

Output: [12,6]

Example 3:

Input: nums = [5,4,9,11]

Output: [5,13,11]



Constraints:

2 <= nums.length <= 100
0 <= nums[i] <= 100
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
using namespace std;

class Solution {
public:
    vector<int> orArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;
        for (int i = 0; i < n - 1; i++) {
            result.push_back(nums[i] | nums[i + 1]);
        }
        return result;
    }
};