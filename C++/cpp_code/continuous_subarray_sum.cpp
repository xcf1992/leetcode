/*
523. Continuous Subarray Sum
https://leetcode.com/problems/continuous-subarray-sum/

Given a list of non-negative numbers and a target integer k,
write a function to check if the array has a continuous subarray of size at least 2 that sums up to the multiple of k,
that is, sums up to n*k where n is also an integer.

Example 1:
Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.

Example 2:
Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.

Note:
The length of the array won't exceed 10,000.
You may assume the sum of all the numbers is in the range of a signed 32-bit integer.
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
using namespace std;
/*
这道题和560题解法一样，强烈建议先看那道题，具体见https://leetcode.com/problems/subarray-sum-equals-k/solution/
当我们分析数组中连续的若干数之和时，很容易想到先用一个数组sm[i]记录sum(nums[:i])，那么则有sm[j] - sm[i] = sum(nums[i:j])
但是如果依次遍历时间复杂度为O(n^2)，在这里肯定超时，所以我们得想个简单的办法，这也就是这类型题的经典思想，前缀和处理
我们先来考虑一个简单的情况，即是否存在连续的子数组的和为k，我们应该怎么做呢？
假设存在i,j满足sum(nums[i:j]) = k，那么则应有sm[j] - sm[i] = k，也就是如果我们找到i,j满足这个式子就可以说明存在…！
那当我们遍历sm数组时，将遍历的数依次存进集合，遍历至sm[j]时，我们如果发现sm[j]-k，即sm[i]是存在于集合中的，那么我们就可以确定,确实存在sum(nums[i:j])
= k 回到我们这道题上，假设确实存在i,j(j-i>=2)满足sum(nums[i:j]) = n * k，即sm[j] - sm[i] = n * k，
此时用上面的方法是不可行的，因为n*k是个不确定的数，我们无法判断其是否在集合内，但我们只用作一个小小的变换————对上式两边同时模k，
上式变为sm[j]%k - sm[i]%k = 0，此时就和4中情况是等价的，唯独是集合中存储的数从sm[i]变成了sm[i]%k
思路：

因为j-i>=2，所以更新集合的时候应当推迟一步，即分析完sm[i]之后才将sm[i-1]%k加入集合之中
注意k = 0的情况，因为模0操作是不被允许的，所以需要单独处理
*/
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (k < 0) {
            k = 0 - k;
        }

        unordered_map<int, int> preSum;
        preSum[0] = -1;
        int curSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            curSum += nums[i];
            if (k != 0) {
                curSum = curSum % k;
            }
            if (preSum.find(curSum) != preSum.end()) {
                if (preSum[curSum] < i - 1) {
                    return true;
                }
            } else {
                preSum[curSum] = i;
            }
        }
        return false;
    }
};