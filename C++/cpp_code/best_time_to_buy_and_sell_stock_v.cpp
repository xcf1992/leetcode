/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-v/description/
3573. Best Time to Buy and Sell Stock V

You are given an integer array prices where prices[i] is the price of a stock in dollars on the ith day, and an integer
k.

You are allowed to make at most k transactions, where each transaction can be either of the following:

Normal transaction: Buy on day i, then sell on a later day j where i < j. You profit prices[j] - prices[i].

Short selling transaction: Sell on day i, then buy back on a later day j where i < j. You profit prices[i] - prices[j].

Note that you must complete each transaction before starting another. Additionally, you can't buy or sell on the same
day you are selling or buying back as part of a previous transaction.

Return the maximum total profit you can earn by making at most k transactions.



Example 1:

Input: prices = [1,7,9,8,2], k = 2

Output: 14

Explanation:

We can make $14 of profit through 2 transactions:
A normal transaction: buy the stock on day 0 for $1 then sell it on day 2 for $9.
A short selling transaction: sell the stock on day 3 for $8 then buy back on day 4 for $2.
Example 2:

Input: prices = [12,16,19,19,8,1,19,13,9], k = 3

Output: 36

Explanation:

We can make $36 of profit through 3 transactions:
A normal transaction: buy the stock on day 0 for $12 then sell it on day 2 for $19.
A short selling transaction: sell the stock on day 3 for $19 then buy back on day 4 for $8.
A normal transaction: buy the stock on day 5 for $1 then sell it on day 6 for $19.


Constraints:

2 <= prices.length <= 103
1 <= prices[i] <= 109
1 <= k <= prices.length / 2
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;
/*
Intuition
This problem is essentially the same as the problem statement of “188. Best Time to Buy and Sell Stock IV”, except that
here we also allow an additional action: short selling. Because of this extra operation, the state definition from the
original problem needs to be extended.

In the editorial for problem 188, the dynamic programming states are defined like this. The value dfs(i, j, 0)
represents the maximum profit after day i if exactly j transactions have been completed and we end the day holding no
stock. Similarly, dfs(i, j, 1) represents the maximum profit after day i with exactly j completed transactions while
holding one stock.

Since this problem allows short selling, meaning we can sell first and buy later, we introduce a third state. The value
dfs(i, j, 2) represents the maximum profit after day i with exactly j completed transactions while holding a short
position.

With these three states defined, consider what can happen on day i when we want to end up with exactly j completed
transactions.

One possibility is that nothing happens on that day. If we neither buy nor sell, then all three states simply carry over
from day i - 1:

dfs(i, j, 0) = dfs(i - 1, j, 0)
dfs(i, j, 1) = dfs(i - 1, j, 1)
dfs(i, j, 2) = dfs(i - 1, j, 2)
Another possibility is that we buy on day i. There are two situations in which this can occur. If we were not holding
anything at the end of day i - 1, buying the stock starts the jth normal transaction, so we come from dfs(i - 1, j - 1,
0) and pay the cost of prices[i], giving dfs(i, j, 1) = dfs(i - 1, j - 1, 0) - prices[i].

The other case is that we were holding a short position. Buying in this situation closes the short transaction, so we
move from dfs(i - 1, j, 2) and again subtract the cost, giving dfs(i, j, 0) = dfs(i - 1, j, 2) - prices[i].

The third possibility on day i is that we sell. If we were holding a stock at the end of the previous day, selling
completes the jth ordinary transaction, so we move from dfs(i - 1, j, 1) and gain prices[i], which results in dfs(i, j,
0) = dfs(i - 1, j, 1) + prices[i].

If instead we were holding nothing at the end of the previous day, selling opens the jth short selling transaction. In
that case we come from dfs(i - 1, j - 1, 0) and add the profit prices[i], which gives dfs(i, j, 2) = dfs(i - 1, j - 1,
0) + prices[i].

These cases lead directly to the final recurrence:

dfs(i,j,0)=max(dfs(i−1,j,0), dfs(i−1,j,1)+prices[i], dfs(i−1,j,2)−prices[i])

dfs(i,j,1)=max(dfs(i−1,j,1), dfs(i−1,j−1,0)−prices[i])

dfs(i,j,2)=max(dfs(i−1,j,2), dfs(i−1,j−1,0)+prices[i])

Next consider the boundary conditions. On day 0, only one price exists. If no action is taken, the profit is zero. If we
buy, the profit is -prices[0]. If we short, the profit is prices[0]. When j = 0, no transactions are allowed, so the
profit must be zero in all states. Translating these observations into formulas:

For all i, if j = 0, then dfs(i, 0, 0) = dfs(i, 0, 1) = dfs(i, 0, 2) = 0.
For i = 0 and any 1 ≤ j ≤ k, we have dfs(0, j, 0) = 0, dfs(0, j, 1) = -prices[0], and dfs(0, j, 2) = prices[0].
After computing all states up to day n - 1, the final answer is dfs(n - 1, k, 0), since we can make at most k total
transactions and we must end with no stock or short position.
-=-=-=-=-

Intuition
At any day, we can either do nothing or be involved in a stock transaction.
Since both normal transactions (buy → sell) and short selling transactions
(sell → buy) are allowed, we can be in three possible states:

Not holding any stock
Holding a long position (bought earlier)
Holding a short position (sold earlier)
Each completed transaction increases the transaction count, and we are allowed
to complete at most k transactions. This naturally leads to a dynamic programming
solution where we make optimal decisions day by day.

Approach
We use recursive dynamic programming with memoization.

Define a recursive function:

dfs(i, t, state)

i → current day
t → number of completed transactions so far
state:
0 → no position
1 → holding a long position
2 → holding a short position
At each day:

We can always choose to skip the day.
If we are not holding any position, we can open a long or short position.
If we are holding a long position, we can sell it to complete a transaction.
If we are holding a short position, we can buy it back to complete a transaction.
Memoization ensures each state is computed only once.
*/
class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        vector<vector<vector<long long>>> memo(n, vector<vector<long long>>(k + 1, vector<long long>(3, -1)));

        function<long long(int, int, int)> dfs = [&](int i, int j, int state) -> long long {
            if (j == 0) {
                return 0;
            }
            if (i == 0) {
                return state == 0 ? 0 : (state == 1 ? -prices[0] : prices[0]);
            }
            if (memo[i][j][state] != -1) {
                return memo[i][j][state];
            }

            int p = prices[i];
            long long res;
            if (state == 0) {
                res = max(dfs(i - 1, j, 0), max(dfs(i - 1, j, 1) + p, dfs(i - 1, j, 2) - p));
            } else if (state == 1) {
                res = max(dfs(i - 1, j, 1), dfs(i - 1, j - 1, 0) - p);
            } else {
                res = max(dfs(i - 1, j, 2), dfs(i - 1, j - 1, 0) + p);
            }
            memo[i][j][state] = res;

            return res;
        };

        return dfs(n - 1, k, 0);
    }
};
