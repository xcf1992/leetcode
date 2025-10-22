/*
309. Best Time to Buy and Sell Stock with Cooldown
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/

Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit.
You may complete as many transactions as you like
(ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)

Example:
Input: [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
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
Definition

Let us define a state machine to model our agent. The state machine consists of three states, which we define as follows:

state held: in this state, the agent holds a stock that it bought at some point before.


state sold: in this state, the agent has just sold a stock right before entering this state. And the agent holds no stock at hand.


state reset: first of all, one can consider this state as the starting point, where the agent holds no stock and did not sell a stock before.
More importantly, it is also the transient state before the held and sold.
Due to the cooldown rule, after the sold state, the agent can not immediately acquire any stock, but is forced into the reset state.
One can consider this state as a "reset" button for the cycles of buy and sell transactions.

At any moment, the agent can only be in one state. The agent would transition to another state by performing some actions, namely:

action sell: the agent sells a stock at the current moment. After this action, the agent would transition to the sold state.

action buy: the agent acquires a stock at the current moment. After this action, the agent would transition to the held state.

action rest: this is the action that the agent does no transaction, neither buy or sell. For instance, while holding a stock at the held state, the agent might simply do nothing, and at the next moment the agent would remain in the held state.

Now, we can assemble the above states and actions into a state machine, which we show in the following graph where each node represents a state, and each edge represents a transition between two states. On top of each edge, we indicate the action that triggers the transition.
Algorithm

In order to implement the above state machine, we could define three arrays (i.e. held[i], sold[i] and reset[i]) which correspond to the three states that we defined before.

Each element in each array represents the maximal profits that we could gain at the specific price point i with the specific state.
For instance, the element sold[2] represents the maximal profits we gain if we sell the stock at the price point price[2].

According to the state machine we defined before, we can then deduce the formulas to calculate the values for the state arrays, as follows:

sold[i]=hold[i−1]+price[i]
held[i]=max(held[i−1],reset[i−1]−price[i])
reset[i]=max(reset[i−1],sold[i−1])

Here is how we interpret each formulas:

sold[i]: the previous state of sold can only be held.
Therefore, the maximal profits of this state is the maximal profits of the previous state plus the revenue by selling the stock at the current price.


held[i]:
the previous state of held could also be held, i.e. one does no transaction.
Or its previous state could be reset, from which state, one can acquire a stock at the current price point.


reset[i]:
the previous state of reset could either be reset or sold.
Both transitions do not involve any transaction with the stock.

Finally, the maximal profits that we can gain from this game would be max(sold[n],reset[n]), i.e. at the last price point, either we sell the stock or we simply do no transaction, to have the maximal profits.
It makes no sense to acquire the stock at the last price point, which only leads to the reduction of profits.

In particular, as a base case, the game should be kicked off from the state reset, since initially we don't hold any stock and we don't have any stock to sell neither.
Therefore, we assign the initial values of sold[-1] and held[-1] to be Integer.MIN_VALUE, which are intended to render the paths that start from these two states impossible.

As one might notice in the above formulas, in order to calculate the value for each array, we reuse the intermediate values, and this is where the paradigm of dynamic programming comes into play.

More specifically, we only need the intermediate values at exactly one step before the current step. As a result, rather than keeping all the values in the three arrays, we could use a sliding window of size 1 to calculate the value for max(sold[n],reset[n]).
*/

class Solution {
public:
    int maxProfit(vector<int>& prices){
        size_t n = prices.size();
        if (n <= 1) {
            return 0;
        }

        vector<int> sold(n, 0);
        sold[0] = INT_MIN;
        vector<int> held(n, 0);
        held[0] = -prices[0];
        vector<int> reset(n, 0);
        reset[0] = 0;
        for (size_t i = 1; i < n; ++i) {
            sold[i] = held[i - 1] + prices[i];
            held[i] = max(held[i - 1], reset[i - 1] - prices[i]);
            reset[i] = max(reset[i - 1], sold[i - 1]);
        }
        return max(sold[n - 1], reset[n - 1]);
    }
};
