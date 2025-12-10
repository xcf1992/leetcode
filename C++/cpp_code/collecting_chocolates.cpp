/*
https://leetcode.com/problems/collecting-chocolates/description/
2735. Collecting Chocolates

You are given a 0-indexed integer array nums of size n representing the cost of collecting different chocolates. The
cost of collecting the chocolate at the index i is nums[i]. Each chocolate is of a different type, and initially, the
chocolate at the index i is of ith type.

In one operation, you can do the following with an incurred cost of x:

Simultaneously change the chocolate of ith type to ((i + 1) mod n)th type for all chocolates.
Return the minimum cost to collect chocolates of all types, given that you can perform as many operations as you would
like.



Example 1:

Input: nums = [20,1,15], x = 5
Output: 13
Explanation: Initially, the chocolate types are [0,1,2]. We will buy the 1st type of chocolate at a cost of 1.
Now, we will perform the operation at a cost of 5, and the types of chocolates will become [1,2,0]. We will buy the 2nd
type of chocolate at a cost of 1. Now, we will again perform the operation at a cost of 5, and the chocolate types will
become [2,0,1]. We will buy the 0th type of chocolate at a cost of 1. Thus, the total cost will become (1 + 5 + 1 + 5 +
1) = 13. We can prove that this is optimal. Example 2:

Input: nums = [1,2,3], x = 4
Output: 6
Explanation: We will collect all three types of chocolates at their own price without performing any operations.
Therefore, the total cost is 1 + 2 + 3 = 6.


Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 109
1 <= x <= 109
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
/*
If we do rotate operation k times,
we can use the min(A[i-k], .. , A[i - 1], A[i]) as the cost for type i.


Explanation
Initilize result array res.
res[k] means the result for k times operation,
and we initilize res[k] = k * x for rotation cost.

To collect type i
we calculate cur = min(A[i-k], .. , A[i - 1], A[i]),
and increment res[k] += cur,
so we calculate the minimum cost to get type i with k operation.

Finally we return the min(res) as final result.

Continue from this solution Rotate

res = min(min(A[i], .. A[i + k]) + kx),
we want to find the minimize min(A[i], .. A[i + k]) + kx with 1 <= k <= n.
 */
class Solution {
public:
    long long minCost(vector<int>& nums, int x) {
    }
};

// rotate
/*
In each rotate just keep track of the minimum of every element and update the sum of all elements at each rotate and the
number of shifts done For example consider array [31 25 18 59] and cost 27. You can do atmost 4 rotate.

shift1 - 31 25 18 59 -> sum(element) + (27)*0 = 133
shift2 - 25 18 18 31 -> sum(element) + (27)*1 = 119
shift3 - 18 18 18 25 -> sum(element) + (27)*2 = 133
shift4 - 18 18 18 18 -> sum(element) + (27)*3 = 153
 */
class Solution {
public:
    long long minCost(vector<int>& nums, int x) {
        int n = nums.size();
        vector<int> min_val(nums.begin(), nums.end());
        long long rst = LLONG_MAX;
        for (int i = 0; i < n; i++) {
            long long sum = 1LL * i * x;
            for (int j = 0; j < n; j++) {
                min_val[j] = min(min_val[j], nums[(j + i) % n]);
                sum += min_val[j];
            }
            rst = min(rst, sum);
        }
        return rst;
    }
};