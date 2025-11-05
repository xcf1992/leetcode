/*
https://leetcode.com/problems/count-ways-to-distribute-candies/description/
1692. Count Ways to Distribute Candies

There are n unique candies (labeled 1 through n) and k bags. You are asked to distribute all the candies into the bags such that every bag has at least one candy.

There can be multiple ways to distribute the candies. Two ways are considered different if the candies in one bag in the first way are not all in the same bag in the second way. The order of the bags and the order of the candies within each bag do not matter.

For example, (1), (2,3) and (2), (1,3) are considered different because candies 2 and 3 in the bag (2,3) in the first way are not in the same bag in the second way (they are split between the bags (2) and (1,3)). However, (1), (2,3) and (3,2), (1) are considered the same because the candies in each bag are all in the same bags in both ways.

Given two integers, n and k, return the number of different ways to distribute the candies. As the answer may be too large, return it modulo 109 + 7.



Example 1:



Input: n = 3, k = 2
Output: 3
Explanation: You can distribute 3 candies into 2 bags in 3 ways:
(1), (2,3)
(1,2), (3)
(1,3), (2)
Example 2:

Input: n = 4, k = 2
Output: 7
Explanation: You can distribute 4 candies into 2 bags in 7 ways:
(1), (2,3,4)
(1,2), (3,4)
(1,3), (2,4)
(1,4), (2,3)
(1,2,3), (4)
(1,2,4), (3)
(1,3,4), (2)
Example 3:

Input: n = 20, k = 5
Output: 206085257
Explanation: You can distribute 20 candies into 5 bags in 1881780996 ways. 1881780996 modulo 109 + 7 = 206085257.


Constraints:

1 <= k <= n <= 1000
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

/*
Suppose dp[k][n] represents the ways to distribute n candies into k bags.

Since each bag needs to have at least one candy, we know that

for any k (bags) > n (candies), the requirement cannot be satisfied,
therefore dp[k][n] = 0 (if k > n)
if k == n, meaning that the number of candies and bags are equal,
we have dp[k][n] = 1 (if k == n) by the equality definition indicated in the description.
To deal with the cases of k < n,
the observation is that dp[k][n] is related to dp[k][n-1] and dp[k-1][n-1] by the following ways:

Suppose we know dp[k][n-1],
which is the ways to distribute n-1 candies into k bags.
To put the n_th candy,
we can put it into any of the existing k bags since all the k bags have candy(s) inside already.
That is, dp[k][n] <-- k * dp[k][n-1].

Suppose we know dp[k-1][n-1].
Now, if we put the n_th candy into a brand new bag,
we have in total n candies distributed in k bags.
That is, dp[k][n] <-- dp[k-1][n-1].
Combined the two parts together, we get dp[k][n] = k * dp[k][n-1] + dp[k-1][n-1].
 */
class Solution {
public:
    int waysToDistribute(int n, int k) {
        long long mod = 1e9 + 7;
        vector<vector<long long> > dp(k + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= k; i++) {
            dp[i][i] = 1;
        }

        for (int i = 1; i <= k; i++) {
            for (int j = i + 1; j <= n; j++) {
                dp[i][j] = (i * dp[i][j - 1] % mod + dp[i - 1][j - 1] % mod) % mod;
            }
        }
        return dp[k][n];
    }
};