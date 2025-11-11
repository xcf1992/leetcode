/*
https://leetcode.com/problems/rearranging-fruits/description/
2561. Rearranging Fruits
Hard
Topics
conpanies icon
Companies
Hint
You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2
representing the cost of fruit in each basket. You want to make both baskets equal. To do so, you can use the following
operation as many times as you want:

Choose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
The cost of the swap is min(basket1[i], basket2[j]).
Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.

Return the minimum cost to make both the baskets equal or -1 if impossible.



Example 1:

Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
Output: 1
Explanation: Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 =
[2,4,1,2]. Rearranging both the arrays makes them equal. Example 2:

Input: basket1 = [2,3,4,1], basket2 = [3,2,5,1]
Output: -1
Explanation: It can be shown that it is impossible to make both the baskets equal.


Constraints:

basket1.length == basket2.length
1 <= basket1.length <= 105
1 <= basket1[i], basket2[i] <= 109
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
#include <map>
using namespace std;

/*
Intuition
The first step is a quick sanity check: for the baskets to become identical, the combined total for every fruit type
must be an even number. If any fruit has an odd total count, it's impossible to split them evenly, so we can stop right
there.

Assuming it's possible, our goal is to fix the imbalance. We identify all the "surplus" fruits—the ones a basket has too
many of compared to its final, ideal share. These are the fruits that need to be moved.

The core of the problem is finding the cheapest way to swap these surplus fruits. For any cheap fruit x that we need to
move, we have two plays:

A direct swap with a more expensive surplus fruit, which costs x.
An indirect swap using the absolute cheapest fruit available (min_val) as a helper. This costs 2 * min_val.
The final strategy is greedy: for every fruit we need to move, we simply pick the cheaper of these two options.
 */
class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        int n = basket1.size();
        map<int, int> fruit_cnt1;
        map<int, int> total_cnt;
        for (int i = 0; i < n; i++) {
            fruit_cnt1[basket1[i]] += 1;
            total_cnt[basket1[i]] += 1;
            total_cnt[basket2[i]] += 1;
        }

        long long min_val = LLONG_MAX;
        for (const auto& [fruit, cnt] : total_cnt) {
            if (cnt % 2 == 1) {
                return -1;
            }
            min_val = min(min_val, (long long)fruit);
        }

        vector<long long> fruit_to_swap;
        for (const auto& [fruit, cnt] : total_cnt) {
            int diff = fruit_cnt1[fruit] - cnt / 2;
            for (int i = 0; i < abs(diff); i++) {
                fruit_to_swap.push_back(fruit);
            }
        }
        sort(fruit_to_swap.begin(), fruit_to_swap.end());

        long long rst = 0;
        for (int i = 0; i < fruit_to_swap.size() / 2; i++) {
            rst += min(2 * min_val, fruit_to_swap[i]);
        }
        return rst;
    }
};
