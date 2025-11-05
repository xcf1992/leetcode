/*
1755. Closest Subsequence Sum
https://leetcode.com/problems/closest-subsequence-sum/

You are given an integer array nums and an integer goal.
You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal.
That is, if the sum of the subsequence's elements is sum,
then you want to minimize the absolute difference abs(sum - goal).

Return the minimum possible value of abs(sum - goal).
Note that a subsequence of an array is an array formed
by removing some elements (possibly all or none) of the original array.

Example 1:
Input: nums = [5,-7,3,5], goal = 6
Output: 0
Explanation: Choose the whole array as a subsequence, with a sum of 6.
This is equal to the goal, so the absolute difference is 0.
Example 2:
Input: nums = [7,-9,15,-2], goal = -5
Output: 1
Explanation: Choose the subsequence [7,-9,-2], with a sum of -4.
The absolute difference is abs(-4 - (-5)) = abs(1) = 1, which is the minimum.
Example 3:
Input: nums = [1,2,3], goal = -7
Output: 7

Constraints:
1 <= nums.length <= 40
-107 <= nums[i] <= 107
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
#include <stdio.h>
#include <set>
#include <numeric>
#include <bitset>
using namespace std;

class Solution {
public:
    int minAbsDifference(vector<int> &ns, int goal) {
        int res = abs(goal), pos = 0, neg = 0;
        for (auto n: ns)
            pos += max(0, n), neg += min(0, n);
        if (goal < neg || goal > pos)
            return min(abs(neg - goal), abs(goal - pos));
        set<int> h1{0}, h2{0};
        for (auto i = 0; i < ns.size() / 2; ++i)
            for (auto n: vector<int>(begin(h1), end(h1)))
                if (h1.insert(n + ns[i]).second)
                    res = min(res, abs(goal - n - ns[i]));
        for (auto i = ns.size() / 2; i < ns.size(); ++i)
            for (auto n: vector<int>(begin(h2), end(h2)))
                if (h2.insert(n + ns[i]).second) {
                    auto it = h1.lower_bound(goal - n - ns[i]);
                    if (it != end(h1))
                        res = min(res, abs(goal - n - ns[i] - *it));
                    if (it != begin(h1))
                        res = min(res, abs(goal - n - ns[i] - *prev(it)));
                    if (res == 0)
                        return res;
                }
        return res;
    }
};