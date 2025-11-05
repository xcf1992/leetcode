/*
1259. Handshakes That Don't Cross
https://leetcode.com/problems/handshakes-that-dont-cross/

You are given an even number of people num_people that stand around a circle
and each person shakes hands with someone else,
so that there are num_people / 2 handshakes total.

Return the number of ways these handshakes could occur such that none of the handshakes cross.
Since this number could be very big, return the answer mod 10^9 + 7

Example 1:
Input: num_people = 2
Output: 1

Example 2:
Input: num_people = 4
Output: 2
Explanation: There are two ways to do it, the first way is [(1,2),(3,4)] and the second one is [(2,3),(4,1)].

Example 3:
Input: num_people = 6
Output: 5

Example 4:
Input: num_people = 8
Output: 14

Constraints:
2 <= num_people <= 1000
num_people % 2 == 0
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
#include "extra_data_types.hpp"
using namespace std;
/*
dp[n] is the number of shaking ways of n pairs people
In the the view of first people in these n pairs,
he/she can choose anyone,
split i pairs on his left and n - 1 - i pairs on his right.

So here comes the equation of dynamic programme:
dp[n + 1] = dp[0] * dp[n] + dp[1] * dp[n - 1] + ..... + dp[n] * dp[0]

Complexity
Time O(N^2)
Space O(N)
*/
class Solution {
public:
    int numberOfWays(int num_people) {
        long mod = 1e9 + 7;
        vector<long> dp(num_people + 1);
        dp[0] = 1;
        for (int k = 1; k <= num_people / 2; ++k) {
            for (int i = 0; i < k; ++i) {
                dp[k] = (dp[k] + dp[i] * dp[k - 1 - i]) % mod;
            }
        }
        return dp[num_people / 2];
    }
};