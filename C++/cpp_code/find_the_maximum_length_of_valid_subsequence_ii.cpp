/*
https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/ Maximum Frequency After Subarray Operation

You are given an array nums of length n. You are also given an integer k.

You perform the following operation on nums once:

Select a subarray nums[i..j] where 0 <= i <= j <= n - 1.
Select an integer x and add x to all the elements in nums[i..j].
Find the maximum frequency of the value k after the operation.

Example 1:
Input: nums = [1,2,3,4,5,6], k = 1
Output: 2
Explanation:
After adding -5 to nums[2..5], 1 has a frequency of 2 in [1, 2, -2, -1, 0, 1].

Example 2:
Input: nums = [10,2,3,4,5,5,4,3,2,2], k = 10
Output: 4
Explanation:
After adding 8 to nums[1..9], 10 has a frequency of 4 in [10, 10, 11, 12, 13, 13, 12, 11, 10, 10].

Constraints:
1 <= n == nums.length <= 105
1 <= nums[i] <= 50
1 <= k <= 50
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
    int maxFrequency(vector<int> &nums, int k) {
        int freq_of_k = count(nums.begin(), nums.end(), k);
        int max_freq = 0;
        for (int num = 1; num <= 50; num++) {
            if (num == k) {
                continue;
            }

            int cur = 0;
            int cur_max = 0;
            for (int n: nums) {
                if (n == num) {
                    cur += 1;
                } else if (n == k) {
                    cur += -1;
                }
                cur = max(cur, 0);
                cur_max = max(cur_max, cur);
            }
            max_freq = max(max_freq, cur_max);
        }
        return freq_of_k + max_freq;
    }
};

/*
The goal is to maximize the frequency of the value k after adding a chosen integer x to a subarray. The optimal approach involves converting as many elements as possible to k by selecting a subarray and an appropriate x.

Approach
Original Count: First, count the existing occurrences of k in the array.
Transformation for Each Value: For each possible value m (1 to 50, except k), create a transformed array where:
m elements contribute +1 (gain if converted to k),
k elements contribute -1 (loss if converted away from k),
Others contribute 0.
Kadane's Algorithm: Use Kadane's algorithm on this transformed array to find the maximum subarray sum, which represents the best possible gain for converting m to k.
Maximize Frequency: The maximum frequency of k is the sum of the original count and the best gain from all possible m.
Complexity
Time Complexity: O(n)
Space Complexity: O(1)

For those still confused why we are adding to cnt directly to the result from Kadane:
Consider what the values we are assigning in Kadane even mean?
In other words, why exactly are we assigning a value of +1 when we encounter an m, −1 when we encounter a k and 0 otherwise?
We want to maximize the number of k in the array.
After the operation is performed the number of k in the array is (assuming k and m are fixed):
Initial count - Number of k in the subarray + Number of m in the subarray
= Initial count + (Number of m in the subarray - Number of k in the subarray)
The value in the bracket is what we need to maximize in order to get the answer, and that is what we are calculating by fixing m (i.e. iterating over all possible m) and subsequently using Kadane.
Note that initial count remains a part of the formula.
To do this we assign a value of 1 to the m and −1 to the k.

This algorithm assumes each number between [1, 50] is present in the list nums. This can be further optimized to account for the case that only part of the numbers are present, so no need to iterate for 50 iterations. Only need to iterate for those numbers that are present in the array.
 */
