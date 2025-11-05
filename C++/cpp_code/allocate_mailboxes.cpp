/*
1478. Allocate Mailboxes
https://leetcode.com/problems/allocate-mailboxes/

Given the array houses and an integer k.
where houses[i] is the location of the ith house along a street,
your task is to allocate k mailboxes in the street.

Return the minimum total distance between each house and its nearest mailbox.
The answer is guaranteed to fit in a 32-bit signed integer.

Example 1:
Input: houses = [1,4,8,10,20], k = 3
Output: 5
Explanation: Allocate mailboxes in position 3, 9 and 20.
Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5

Example 2:
Input: houses = [2,3,5,12,18], k = 2
Output: 9
Explanation: Allocate mailboxes in position 3 and 14.
Minimum total distance from each houses to nearest mailboxes is |2-3| + |3-3| + |5-3| + |12-14| + |18-14| = 9.

Example 3:
Input: houses = [7,4,6,1], k = 1
Output: 8

Example 4:
Input: houses = [3,6,14,10], k = 4
Output: 0

Constraints:
n == houses.length
1 <= n <= 100
1 <= houses[i] <= 10^4
1 <= k <= n
Array houses contain unique integers.
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
Explantion
dp[i] will means that,
the minimum distance of i + 1 first house.

B[i] = A[0] + A[1] + A[2] + .. + A[i-1]
cal(i, j) will return the minimum distance,
between A[i]~A[j] with only one mailbox.

Initialy, when k = 1, dp[i] = cal(0, i)
when we increment k, we can update dp with one more mailbox added.

Here we brute force the number of houses that new mailbox in charge.
The brute force here are good enough to get accepted.


Explantion for the cost
What and why is last = (B[j + 1] - B[m2]) - (B[m1 + 1] - B[i + 1]);

All from @caohuicn:

First of all,
last is to calculate distances for houses [i + 1, j] with 1 mailbox,
since the dp recurrence relation is:
dp[j][k] = min(dp[i][k-1] + cal[i + 1, j])
(second dimension is implicit in the code);

For houses [i + 1, j],
if the number of houses is odd,
the only mailbox should always be placed in the middle house.
If number of house is even, it can be placed anywhere
between the middle 2 houses.

Let's say we always put it at m1;
Now let's see the meaning of m1 and m2. For even houses,
m1 + 1 == m2, for odd houses, m1 == m2.
The point of introducing 2 variables is to
make sure number of houses between [i+1, m1] and [m2,j] are always equal.
(B[j + 1] - B[m2]) means A[m2] + A[m2+1] + ... + A[j],
(B[m1 + 1] - B[i + 1]) means A[i+1] + A[i+2] + ... + A[m1],
so last becomes A[j] - A[i+1] + A[j-1] - A[i+2] +... + A[m2] - A[m1].

We can interpret it as:
if the mailbox is placed between any 2 houses x and y,
the sum of distances for both houses will be A[y] - A[x].
Say we have 2n houses, then there will be n pairs;
if we have 2n + 1 houses, then there will n + 1 pairs.
Another way to interpret it is:
if the mailbox is placed at m1,
for all the right side houses,
the sum of distances will be
A[m2]-A[m1] + A[m2+1]-A[m1] + ... + A[j]-A[m1],
and for the left side (including m1),
it'll be A[m1]-A[i+1]+A[m1]-A[i+2]+...+A[m1]-A[m1-1] + A[m1]-A[m1].

Adding these 2 things together,
A[m1]s will be cancelled out,
since number of houses between [i+1, m1] and [m2,j] are always equal.

Hope it helps.

Complexity
Time O(KNN)
Space O(N)
*/
#define MAX 100
#define INF 1000000

class Solution {
public:
    int costs[MAX][MAX] = {};
    int memo[MAX][MAX] = {};

    int minDistance(vector<int> &houses, int k) {
        int n = houses.size();
        sort(houses.begin(), houses.end());
        memset(memo, -1, sizeof(memo));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int t = i; t <= j; t++)
                    costs[i][j] += abs(houses[(i + j) / 2] - houses[t]);
        return dp(houses, n, k, 0);
    }

    int dp(vector<int> &houses, int n, int k, int i) {
        if (k == 0 && i == n) return 0;
        if (k == 0 || i == n) return INF;
        if (memo[k][i] != -1) return memo[k][i];
        int ans = INF;
        for (int j = i; j < n; j++)
            ans = min(ans, costs[i][j] + dp(houses, n, k - 1, j + 1));
        return memo[k][i] = ans;
    }
};