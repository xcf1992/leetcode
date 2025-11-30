/*
1793. Maximum Score of a Good Subarray
https://leetcode.com/problems/maximum-score-of-a-good-subarray/

You are given an array of integers nums (0-indexed) and an integer k.
The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ..., nums[j]) * (j - i + 1).
A good subarray is a subarray where i <= k <= j.
Return the maximum possible score of a good subarray.

Example 1:
Input: nums = [1,4,3,7,4,5], k = 3
Output: 15
Explanation: The optimal subarray is (1, 5) with a score of min(4,3,7,4,5) * (5-1+1) = 3 * 5 = 15.
Example 2:
Input: nums = [5,5,4,5,4,1,1,1], k = 0
Output: 20
Explanation: The optimal subarray is (0, 4) with a score of min(5,5,4,5,4) * (4-0+1) = 4 * 5 = 20.

Constraints:
1 <= nums.length <= 105
1 <= nums[i] <= 2 * 104
0 <= k < nums.length
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
/*
We start with i = j = k, the score = A[k].
When increment the size of window,
we want to reduce the min(A[i]..A[j]) slowly.

To do this, we can check the values on both sides of the window.
If A[i - 1] < A[j + 1], we do j = j + 1
If A[i - 1] >= A[j + 1], we do i = i - 1

During this process,
there is sense that we reduce min(A[i]..A[j]) step by step.
*/
class Solution {
public:
    int maximumScore(vector<int>& A, int k) {
        int res = A[k], mini = A[k], i = k, j = k, n = A.size();
        while (i > 0 or j < n - 1) {
            if ((i > 0 ? A[i - 1] : 0) < (j < n - 1 ? A[j + 1] : 0))
                mini = min(mini, A[++j]);
            else
                mini = min(mini, A[--i]);
            res = max(res, mini * (j - i + 1));
        }
        return res;
    }
};