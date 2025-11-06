/*
1671. Minimum Number of Removals to Make Mountain Array
https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/

You may recall that an array arr is a mountain array if and only if:
arr.length >= 3
There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain
array.

Example 1:
Input: nums = [1,3,1]
Output: 0
Explanation: The array itself is a mountain array so we do not need to remove any elements.

Example 2:
Input: nums = [2,1,1,5,6,2,3,1]
Output: 3
Explanation: One solution is to remove the elements at indices 0, 1, and 5, making the array nums = [1,5,6,3,1].

Example 3:
Input: nums = [4,3,2,1,1,2,3,1]
Output: 4

Example 4:
Input: nums = [1,2,3,4,4,3,2,1]
Output: 1

Constraints:
3 <= nums.length <= 1000
1 <= nums[i] <= 109
It is guaranteed that you can make a mountain array out of nums.
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
#include <cfloat>
#include <stdio.h>
#include <map>
#include <set>
#include <list>
#include <numeric>
#include <random>
#include <vector>
#include "extra_data_types.hpp"
using namespace std;
/*
See my latest update in repo LeetCode

Solution 1. Three passes O(NlogN)
Intuition
Assume we pick A[i] as the peak of the mountain, then we are looking for the longest increasing subsequence to the left
of A[i], and the longest decreasing subsequence to the right of A[i].

We can reuse the O(NlogN) time binary search solution to 300. Longest Increasing Subsequence (Medium).

For the binary search solution to problem 300, please checkout my explanation.

Algorithm
Let a[i] be the length of the longest increasing subsequence in A[0..(i-1)], and b[i] be the length of the longest
decreasing subsequence in A[(i+1)..(N-1)].

We can scan from left to right to set the a[i] values, and scan from right to left to set the b[i] values.

For 1 <= i <= N - 2, the longest mountain size is a[i] + b[i] + 1.

So the answer is the minimum N - (a[i] + b[i] + 1).

Note that we need to skip cases where either a[i] or b[i] is zero because it's invalid.

Test cases that should be added:

[1,2,1,2,3,4] and [4,3,2,1,2,1]. Correct answer is 3.
[1,2,1,1,2,3,4,5] and [5,4,3,2,1,1,2,1]. Correct answer is 5.
*/
class Solution {
public:
    int minimumMountainRemovals(vector<int>& A) {
        int N = A.size();
        vector<int> a(N), b(N), v;
        for (int i = 0; i < N; ++i) {
            int x = A[i];
            auto it = lower_bound(begin(v), end(v), x);
            a[i] = it - begin(v);
            if (it != end(v)) {
                *it = x;
            } else {
                v.push_back(x);
            }
        }

        v.clear();
        for (int i = N - 1; i >= 0; --i) {
            int x = A[i];
            auto it = lower_bound(begin(v), end(v), x);
            b[i] = it - begin(v);
            if (it != end(v)) {
                *it = x;
            } else {
                v.push_back(x);
            }
        }

        int ans = N;
        for (int i = 1; i < N - 1; ++i) {
            if (a[i] == 0 || b[i] == 0) {
                continue;
            }
            ans = min(ans, N - (a[i] + b[i] + 1));
        }
        return ans;
    }
};