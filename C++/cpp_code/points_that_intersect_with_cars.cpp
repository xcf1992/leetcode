/*
https://leetcode.com/problems/points-that-intersect-with-cars/description/
2848. Points That Intersect With Cars
Easy
Topics
conpanies icon
Companies
Hint
You are given a 0-indexed 2D integer array nums representing the coordinates of the cars parking on a number line. For
any index i, nums[i] = [starti, endi] where starti is the starting point of the ith car and endi is the ending point of
the ith car.

Return the number of integer points on the line that are covered with any part of a car.



Example 1:

Input: nums = [[3,6],[1,5],[4,7]]
Output: 7
Explanation: All the points from 1 to 7 intersect at least one car, therefore the answer would be 7.
Example 2:

Input: nums = [[1,3],[5,8]]
Output: 7
Explanation: Points intersecting at least one car are 1, 2, 3, 5, 6, 7, 8. There are a total of 7 points, therefore the
answer would be 7.


Constraints:

1 <= nums.length <= 100
nums[i].length == 2
1 <= starti <= endi <= 100
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
#include <map>
using namespace std;

class Solution {
public:
    int numberOfPoints(vector<vector<int>>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end(), [](const vector<int>& a, const vector<int>& b) {
           return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
        });

        int rst = 0;
        int start = nums[0][0];
        int end = nums[0][1];
        for (int i = 1; i < n; i++) {
            if (end >= nums[i][0]) {
                end = max(end, nums[i][1]);
                continue;
            }

            rst += end - start + 1;
            start = nums[i][0];
            end = nums[i][1];
        }
        rst += end - start + 1;
        return rst;
    }
};