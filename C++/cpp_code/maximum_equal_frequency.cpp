/*
1224. Maximum Equal Frequency
https://leetcode.com/problems/maximum-equal-frequency/

Given an array nums of positive integers,
return the longest possible length of an array prefix of nums,
such that it is possible to remove exactly one element from this prefix
so that every number that has appeared in it will have the same number of occurrences.

If after removing one element there are no remaining elements,
it's still considered that every appeared number has the same number of ocurrences (0).

Example 1:
Input: nums = [2,2,1,1,5,3,3,5]
Output: 7
Explanation: For the subarray [2,2,1,1,5,3,3] of length 7, if we remove nums[4]=5, we will get [2,2,1,1,3,3], so that each number will appear exactly twice.

Example 2:
Input: nums = [1,1,1,2,2,2,3,3,3,4,4,4,5]
Output: 13

Example 3:
Input: nums = [1,1,1,2,2,2]
Output: 5

Example 4:
Input: nums = [10,2,8,9,3,8,1,5,2,3,7,6]
Output: 8

Constraints:
2 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
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
#include "extra_data_types.hpp"
using namespace std;
/*
Intuition
We need to count the frequency of numbers in A
Also we need to know, for each frequency, we have how many different numbers.
count[a] means the frequency of number a
freq[c] means how many numbers that occur c times.

Explanation
Iterate the input array A and we count the n first numbers.

There actually only 2 situation to discuss:
we delete the current number a.
In this case, the n - 1 first numbers have the same frequency,
and we can easier detect this case when we iterate the previous number A[n - 1]

we don't delete the current number a
the current a occurs c times.
So except all numbers that also occurs c times,
it should leave one single number, or c + 1 same numeber.

That's it, done.

Complexity
Time O(N)
Space O(K), where K = set(A).length
*/
class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return n;
        }

        vector<int> count(1e5 + 1, 0);
        vector<int> freq(1e5 + 1, 0);
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            int num = nums[i - 1];
            freq[count[num]] -= 1;
            int curCount = ++count[num];
            freq[curCount] += 1;

            if (freq[curCount] * curCount == i and i < n) {
                result = i + 1;
            }
            int gap = i - freq[curCount] * curCount;
            if ((gap == curCount + 1 or gap == 1) and freq[gap] == 1) {
                result = i;
            }
        }
        return result;
    }
};
