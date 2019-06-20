/*
312. Burst Balloons

Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums.
You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins.
Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:

You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
Example:

Input: [3,1,5,8]
Output: 167
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
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
using namespace std;

/*
I think the most upvoted post didn't talk about what dp[i][j] represent and what exactly does the transition function :

for (int k = left; k <= right; ++k)
dp[left][right] = max(dp[left][right], nums[left-1] * nums[k] * nums[right+1] + dp[left][k-1] + dp[k+1][right])**
means.

Or maybe it did talk about it but I miss it. But anyway here is my understand of this problem after reading countless of posts and comments :

First of all, dp[i][j] in here means, the maximum coins we get after we burst all the balloons between i and j in the original array.

For example with input [3,1,5,8] :

dp[0][0] means we burst ballons between [0,0], which means we only burst the first balloon in original array. So dp[0][0] is 1 * 3 * 1 = 3.

dp[1][1] means we burst balloons between [1][1], which means we only burst the second ballon in the original array. So dp[1][1] is 3 * 1 * 5 = 15.

So in the end for this problem we want to find out dp[0][ arr.length - 1 ], which is the maximum value we can get when we burst all the balloon between [0 , length -1]

To get that we need the transition function :

for (int k = left; k <= right; ++k)
dp[left][right] = max(dp[left][right], nums[left-1] * nums[k] * nums[right+1] + dp[left][k-1] + dp[k+1][right])**

This transition function basically says in order to get the maximum value we can get for bursting all the balloons between [ i , j] , we just loop through each balloon between these two indexes and make them to be the last balloon to be burst,

why we pick it as the last balloon to burst ?

For example when calculating dp[0,3] and picking index 2 as the last balloon to burst,

[ 3 , 1 , 5 , 8] , that means 5 is the last balloon to burst between [0,3] , to get the maximum value when picking 5 as the last balloon to burst :

max = maximum value of bursting all the balloon on the left side of 5 + maximum value of bursting all the balloon on the right side of 5 + bursting balloon 5 when left side and right side are gone.

That is dp[0, 1] + nums[0 - 1] * nums[2] * nums[3 + 1] + + dp[3,3];

That is dp[left, k - 1] + nums[left - 1] * nums[k] * nums[right + 1] + dp[k+1, right] ;

to get the maximum dp[left, right] we just loop through all the possible value of k to get the maximum.

Hope it helps!
*/
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        for (int len = 1; len <= n; ++len) {
            for (int start = 1; start + len - 1 <= n; ++start) {
                int end = start + len - 1;
                for (int mid = start; mid <= end; ++mid) {
                    dp[start][end] = max(dp[start][end], dp[start][mid - 1] + nums[start - 1] * nums[mid] * nums[end + 1] + dp[mid + 1][end]);
                }
            }
        }
        return dp[1][n];
    }
};
