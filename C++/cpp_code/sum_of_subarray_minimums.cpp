/*
907. Sum of Subarray Minimums
https://leetcode.com/problems/sum-of-subarray-minimums/

Given an array of integers A, find the sum of min(B),
where B ranges over every (contiguous) subarray of A.

Since the answer may be large, return the answer modulo 10^9 + 7.

Example 1:
Input: [3,1,2,4]
Output: 17
Explanation: Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.  Sum is 17.

Note:
1 <= A.length <= 30000
1 <= A[i] <= 30000
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
using namespace std;
/*
I guess this is a general intuition for most solution.
res = sum(A[i] * f(i))
where f(i) is the number of subarrays,
in which A[i] is the minimum.

To get f(i), we need to find out:
left[i], the length of strict bigger numbers on the left of A[i],
right[i], the length of bigger numbers on the right of A[i].

Then,
left[i] + 1 equals to
the number of subarray ending with A[i],
and A[i] is single minimum.

right[i] + 1 equals to
the number of subarray starting with A[i],
and A[i] is the first minimum.

Finally f(i) = (left[i] + 1) * (right[i] + 1)

For [3,1,2,4] as example:
left + 1 = [1,2,1,1]
right + 1 = [1,3,2,1]
f = [1,6,2,1]
res = 3 * 1 + 1 * 6 + 2 * 2 + 4 * 1 = 17

Explanation:
To calculate left[i] and right[i],
we use two increasing stacks.

It will be easy if you can refer to this problem and my post:
901. Online Stock Span
I copy some of my codes from this solution.

Improvement
1.Here I record (A[i], count) in the stack.
We can also only record index.
2. For left part and right part, the logic is same.
So I used one stack and pass each.
This process can be optimized to one pass using one stack in total.

More:
For some more similar problem, I suggest
828. Unique Letter String
891. Sum of Subsequence Widths

Complexity:
All elements will be pushed twice and popped at most twice
O(N) time, O(N) space

as we can count duplicate minimum in the same subarry once
for example [3,1,1,2,4]
the subarray[1,1] should only be provide minimum 1 once
*/
class Solution {
private:
    int MOD = 1e9 + 7;

public:
    int sumSubarrayMins(vector<int>& A) {
        int n = A.size();
        vector<int> left(n, 0);
        vector<int> right(n, 0);
        stack<pair<int, int>> stk1, stk2;
        for (int i = 0; i < n; i++) {
            int count = 1;
            while (!stk1.empty() and stk1.top().first > A[i]) {
                // the count of number A[j] which > A[i], where j <= i
                count += stk1.top().second;
                stk1.pop();
            }
            stk1.push({A[i], count});
            left[i] = count;

            int j = n - 1 - i;
            count = 1;
            while (!stk2.empty() and stk2.top().first >= A[j]) {
                // the count of number A[j] which >= A[i], where j >= i
                count += stk2.top().second;
                stk2.pop();
            }
            stk2.push({A[j], count});
            right[j] = count;
        }

        int result = 0;
        for (int i = 0; i < n; i++) {
            result = (result + A[i] * left[i] * right[i]) % MOD;
        }
        return result;
    }
};