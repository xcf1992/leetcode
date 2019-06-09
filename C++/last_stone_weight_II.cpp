/*
 1049. Last Stone Weight II

 We have a collection of rocks, each rock has a positive integer weight.
 
 Each turn, we choose any two rocks and smash them together.  
 Suppose the stones have weights x and y with x <= y.  
 The result of this smash is:
 
 If x == y, both stones are totally destroyed;
 If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
 At the end, there is at most 1 stone left.  Return the smallest possible weight of this stone (the weight is 0 if there are no stones left.)
 
 Example 1:
 
 Input: [2,7,4,1,8,1]
 Output: 1
 Explanation:
 We can combine 2 and 4 to get 2 so the array converts to [2,7,1,8,1] then,
 we can combine 7 and 8 to get 1 so the array converts to [2,1,1,1] then,
 we can combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
 we can combine 1 and 1 to get 0 so the array converts to [1] then that's the optimal value.
 
 
 Note:
 
 1 <= stones.length <= 30
 1 <= stones[i] <= 100

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
#include <set>
#include <numeric>
using namespace std;

/*
DP of backpack problem 
Divide all numbers into two groups,
what is the minimum difference between the sum of two groups.
Now it's a easy classic knapsack problem.

As this problem will be quite boring as Q4 (if you read my post),
I'll leave you a slightly harder problem as follow-up just for more fun.
Question: Return the biggest possible weight of this stone?


FAQ (Some high voted questions)
Question: How is it a knapsack problem?
My understanding of Knapsack problem is this-
You are given a set of items , for each of which we have a weight w[i] and value v[i].
Now we have a bag for capacity W and we maximize our profit.
Answer:
w[i] = 1
v[i] = stones[i]
W = sum(stones) / 2

=*=*=*=*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*=*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*=
Question: Why the minimum result of cancellation is equal to minimum knapsack partition?
Answer:

One cancellation can be represented as one grouping.
One grouping can be represented as one knapsack partition.
If the grouping difference < max(A), it can be realized by a cancellation.
With the 2 conclusions above,
we can know that the minimum result of cancellation is equal to minimum grouping difference,
which we solved by knapsack problem.

Question: In some version of solution, what does the magic number 1500 mean?
Answer:
The dp[i] present if the sum of one group can be i.
So we can only record the smaller one for less space cost,
which less than half of the upper bound of total sum 3000.

=*=*=*=*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*=*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*=
Proof that the minimum can be achieved, inspired by @sizfeetunder 's post (which looks like an incomplete proof to me):
Given stones {x_1, ..., x_k}, let
a(x_1, ..., x_k) be the minimum among all expressions of the form (y_1+...+y_m) - (z_1+...+z_n) that are >= 0 such that {x_1,...x_k} is the disjoint union of {y_1,...,y_m} and {z_1,...z_n} (i.e. a solution of the corresponding knapsack problem), and let
b(x_1, ..., x_k) be the minimum final stone starting from {x_1,...,x_k}.
Since any final stone can be written in the form (y_1+...+y_m) - (z_1+...+z_n), we have b >= a (Ineq 0).
We show a(x_1,...,x_k) = b(x_1,...,x_k) by induction:
if k = 0 or k = 1, it is trivial that a = b;
if k >= 2, write a(x_1,...,x_k) = (y_1+...+y_m) - (z_1+...+z_n) (Eq 1), then clearly m >= 1 and n >= 1.

If y_1 > z_1, consider ((y_1-z_1)+(y_2+...+y_m)) - (z_2+...+z_n); we know that it is >= 0, so it is >= the minimum a(y_1-z_1, y_2,...,y_m, z_2,...,z_n) (Ineq 1).
By induction hypothesis (we've reduced the number of stones by one), a(y_1-z_1, y_2,...,y_m, z_2,...,z_n) = b(y_1-z_1, y_2,...,y_m, z_2,...,z_n) (Eq 2).
Note that b(x_1, ..., x_k) is the minimum among all first-step choices of two stones to cancel. Since {y_1,z_1} is one possible choice, we have b(y_1-z_1, y_2,...,y_m, z_2,...,z_n) >= b(x_1, ..., x_k) (Ineq 2).
Combining (Eq 1), (Ineq 1), (Eq 2) and (Ineq 2), we get a(x_1,...,x_k) >= b(x_1,...,x_k), hence a(x_1,...,x_k) = b(x_1,...,x_k) by (Ineq 0).
If y_1 < z_1, consider (y_2+...+y_m) - ((z_1-y_1)+z_2+...+z_n) and the same reasoning applies.
If y_1 = z_1, consider (y_2+...+y_m) - (z_2+...+z_n) and the same reasoning applies.
In the last case we reduce the number of stones by two. We've shown that a=b for any k stones given that a=b for any (k-1) stones and any (k-2) stones. By induction we know a=b for any number of stones.

=*=*=*=*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*=*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*==*=*=*=
Proof that the max final weight is (the max stone) - (the min final stone from the remaining stones):
Let J - K be the last cancellation to get the max final stone, where J and K each is an original stone or obtained from some cancellations. I claim that J must be an original stone: otherwise J = L - H and hence J - K = L - (H+K). But then L - |H-K| is larger and can also be obtained, contradicting our assumption.
It remains to show that J - (min final stone from the remaining) achieves maximum when L is the max stone M.
If J is not the max, the max stone M appears in K when K is written as (sum of some stones) - (sum of remaining stones).
So K = M + K1 - K2 or K = K1 - K2 - M.

If K = K1 - K2 - M, we have J - K = J - (K1 - K2 - M) = M - (K1 - K2 - J). Since K1 - K2 - M = K >= 0 and M > J, we have K1 - K2 - J > 0, so the minimum final stone obtained from the stones in K1, K2 and J is at most K1 - K2 - J, so M - (min final from J,K1,K2) >= M - (K1 - K2 - J) = J - K.
If K = M + K1 - K2, we have J - K = J - (M + K1 - K2). Now consider M - (J + K1 - K2). We know M + K1 - K2 = K >= 0, but J + K1 - K2 may be < 0. (In fact it must be if J-K is the max, otherwise M-(J+K1-K2) >= J-(M+K1-K2) contradicting maximality.) However, we still know that the minimum final stone from stones in K1, K2 and J is at most |J+K1-K2|, and it is always true that |J+K1-K2| <= (M+K1-K2) + (M-J) (a special case of the triangle inequality |a+b| <= |a| + |b|). So M - (min final from J,K1,K2) >= M - |J+K1-K2| >= M - (M-J) - (M+K1-K2) = J - K.
*/
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        vector<bool> dp(sum + 1, false);
        dp[0] = true;

        int cur = 0;
        for (int stone : stones) {
            cur += stone;
            for (int i = cur; i >= stone; --i) {
                if (dp[i - stone]) {
                    dp[i] = true;
                }
            }
        }

        for (int i = sum / 2; i > 0; --i) {
            if (dp[i]) {
                return sum - i - i;
            }
        }
        return 0;
    }
};

/*
 1. Think of the final answer as a sum of weights with + or - sign symbols infront of each weight. Actually, all sums with 1 of each sign symbol are possible.
 2. Use dynamic programming: for every possible sum with N stones, those sums +x or -x is possible with N+1 stones, where x is the value of the newest stone. (This overcounts sums that are all positive or all negative, but those don't matter.)
 https://leetcode.com/problems/last-stone-weight-ii/discuss/295401/C%2B%2B-DP-inspired-by-the-hints-double-100-with-explanation
 */
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        unordered_set<int> stoneLeft;
        for (int& stone : stones) {
            if (stoneLeft.empty()) {
                stoneLeft.insert(stone);
                stoneLeft.insert(-stone);
            }
            else {
                unordered_set<int> temp;
                for (int left : stoneLeft) {
                    temp.insert(left + stone);
                    temp.insert(left - stone);
                }
                stoneLeft = temp;
            }
        }
        
        int result = INT_MAX;
        for (int left : stoneLeft) {
            if (left >= 0) {
                result = min(left, result);
            }
        }
        return result;
    }
};
