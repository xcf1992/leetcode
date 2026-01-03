/*
https://leetcode.com/problems/maximize-greatness-of-an-array/description/
2592. Maximize Greatness of an Array

You are given a 0-indexed integer array nums. You are allowed to permute nums into a new array perm of your choosing.

We define the greatness of nums be the number of indices 0 <= i < nums.length for which perm[i] > nums[i].

Return the maximum possible greatness you can achieve after permuting nums.



Example 1:

Input: nums = [1,3,5,2,1,3,1]
Output: 4
Explanation: One of the optimal rearrangements is perm = [2,5,1,3,3,1,1].
At indices = 0, 1, 3, and 4, perm[i] > nums[i]. Hence, we return 4.
Example 2:

Input: nums = [1,2,3,4]
Output: 3
Explanation: We can prove the optimal perm is [2,3,4,1].
At indices = 0, 1, and 2, perm[i] > nums[i]. Hence, we return 3.


Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
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
#include <climits>
using namespace std;

/*
Imagine A is sorted,
and we try to satify as many as possible but k elements.

How will we arrange the list?

before: A[0] A[1] ... A[n - 1 - k]
after: A[k] A[1+k] ... A[n - 1]

where
A[0] < A[k]
A[1] < A[1 + k]
A[2] < A[2 + k]
...
A[n - 1 - k] < A[n - 1]

This greedy arrange is the best plan to satify as many pairs as possible.
Note that k need to be bigger than the biggest frequency of A[i],
otherwise there will be at least one A[i] == A[i + k].

So the problem now is to find out the maximum frequency of A.

What the problem asks
You need to rearrange array A into array B such that the number of indices where B[i] > A[i] is maximized. This count is
called the "greatness." What this solution does Key insight: The maximum greatness equals total elements - frequency of
most common element Here's why: The algorithm:

Count frequency of each element using a hash map
Track the maximum frequency k
Return A.size() - k

Why this works:
Imagine you have array [1,2,2,2,3]:

Most frequent element: 2 appears 3 times
You can pair elements optimally so every element finds a larger partner, EXCEPT those 3 copies of 2 can't all find
larger partners (since there aren't 3 elements larger than 2) At best, you can match 2 elements: the two 2s can pair
with 3 and nothing, but one 2 must "waste" a position Greatness = 5 - 3 = 2 ✓

General principle: The most frequent element is the bottleneck. If it appears k times, at least k positions can't be
improved (we can't make k elements all greater than themselves when they're the same value and there aren't enough
larger elements). This greedy counting approach elegantly avoids the complexity of actually constructing the optimal
rearrangement - it just calculates the theoretical maximum directly.
 */
class Solution {
public:
    int maximizeGreatness(vector<int>& A) {
        unordered_map<int, int> count;
        int k = 0;
        for (int a : A)
            k = max(k, ++count[a]);
        return A.size() - k;
    }
};

class Solution {
public:
    int maximizeGreatness(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> temp = nums;
        int n = temp.size();
        int rst = 0;
        int temp_idx = 0;
        for (int i = 0; i < n; i++) {
            while (temp_idx < n && temp[temp_idx] <= nums[i]) {
                temp_idx += 1;
            }
            if (temp_idx < n) {
                rst += 1;
                temp_idx += 1;
            } else {
                break;
            }
        }
        return rst;
    }
};
