/*
1388. Pizza With 3n Slices
https://leetcode.com/problems/pizza-with-3n-slices/

There is a pizza with 3n slices of varying size,
you and your friends will take slices of pizza as follows:

You will pick any pizza slice.
Your friend Alice will pick next slice in anti clockwise direction of your pick.
Your friend Bob will pick next slice in clockwise direction of your pick.
Repeat until there are no more slices of pizzas.
Sizes of Pizza slices is represented by circular array slices in clockwise direction.

Return the maximum possible sum of slice sizes which you can have.

Example 1:
Input: slices = [1,2,3,4,5,6]
Output: 10
Explanation: Pick pizza slice of size 4, Alice and Bob will pick slices with size 3 and 5 respectively. Then Pick slices with size 6, finally Alice and Bob will pick slice of size 2 and 1 respectively. Total = 4 + 6.

Example 2:
Input: slices = [8,9,8,6,1,1]
Output: 16
Output: Pick pizza slice of size 8 in each turn. If you pick slice with size 9 your partners will pick slices of size 8.

Example 3:
Input: slices = [4,1,2,5,8,3,1,9,7]
Output: 21

Example 4:
Input: slices = [3,1,2]
Output: 3

Constraints:
1 <= slices.length <= 500
slices.length % 3 == 0
1 <= slices[i] <= 1000
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
#include <stdio.h>
#include "extra_data_types.hpp"
using namespace std;
/*
Someone happened to ask me this problem ealier.
I told him to do this 213. House Robber II
Almost the same.


Intuition
The interruption of this question is:
get n elements from an an array of sizes 3*n.
None of the selected n elements could be neighbor to each others.
And because its in cycle,
A[0] and A[n-1] cannot be chosen together.
After understanding this, the question become much easier.


Explanation
Each round, we will decide if we take the last slice in A[i]~A[j].
If we take it, we will take the rest k-1 slices in A[i]~A[j-2]
If we don't take it, we will take the rest k slices in A[i]~A[j-1]

Why do we check j - i + 1 < k * 2 - 1,
instead of something like (k-1) < j - i +1 <= 3 * k

@caohuicn help explain this part:
Because j - i + 1 is not the number of all the slices that are left.
You might have chosen not to take a slice in a previous step,
then there would be leftovers outside of [i, j].
Now if you take i or j (the start or end slice),
one of the slices your friends take will be outside of [i, j],
so the length of [i, j] is reduced by 2, not 3.
Therefore the minimum number is 2 * k - 1
(the last step only requires one slice).

Note that dfs can be compressed to one line but too long.

A little more explanation for other bros not as smart as lee..(like me )

why circle = 0 in recursive is ok..which mean do not need to consider the circle anymore in the dp progress..?
The target is equal to find the max sum sequence sized n//3 and each element is not adjacent...order is not important and when they are not adjacent, it is always possible to find a legal order to take.

for example.... [x1, x2, x3, x4, x5,x6,x7,x8,x9]...the task is to pick 3 of them... assume x2..x7..x9 is larger than anyone...so x2+x7+x9 must be the answer
In the above function, we take x9 and dp [x2,x3,x4,x5,x6,x7]...this is obvious....then we take x7 and dp[x2, x3, x4,x5]...someone may think..oh no..when x7 is taken..we should delete x2 also...this is not ok...actually this is just not ok in this taking order...first x9, next x7...x2 is impossible....however...first x2, next x7 or x9....it is legal.
*/
class Solution {
private:
    unordered_map<string, int> memo;

    int dp(vector<int>& slices, int start, int end, int n, int cycle) {
        string key = to_string(start) + "$" + to_string(end) + "$" + to_string(n) + "$" + to_string(cycle);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }

        if (n == 1) {
            int temp = INT_MIN;
            for (int i = start; i <= end; ++i) {
                temp = max(temp, slices[i]);
            }
            memo[key] = temp;
            return memo[key];
        }

        if (end - start + 1 < n * 2 - 1) {
            memo[key] = INT_MIN;
            return memo[key];
        }

        int res = max(dp(slices, start + cycle, end - 2, n - 1, 0) + slices[end],
                      dp(slices, start, end - 1, n, 0));
        memo[key] = res;
        return memo[key];
    }
public:
    int maxSizeSlices(vector<int>& slices) {
        int n = slices.size();
        return dp(slices, 0, n - 1, n / 3, 1);
    }
};
