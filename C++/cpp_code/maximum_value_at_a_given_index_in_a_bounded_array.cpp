/*
1802. Maximum Value at a Given Index in a Bounded Array
https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/

You are given three positive integers n,
index and maxSum.
You want to construct an array nums (0-indexed) that satisfies the following conditions:
nums.length == n
nums[i] is a positive integer where 0 <= i < n.
abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
The sum of all the elements of nums does not exceed maxSum.
nums[index] is maximized.
Return nums[index] of the constructed array.
Note that abs(x) equals x if x >= 0, and -x otherwise.

Example 1:
Input: n = 4, index = 2,  maxSum = 6
Output: 2
Explanation: The arrays [1,1,2,1] and [1,2,2,1] satisfy all the conditions. There are no other valid arrays with a
larger value at the given index. Example 2: Input: n = 6, index = 1,  maxSum = 10 Output: 3

Constraints:
1 <= n <= maxSum <= 109
0 <= index < n
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
using namespace std;
/*
We first do maxSum -= n,
then all elements needs only to valid A[i] >= 0

We binary search the final result between left and right,
where left = 0 and right = maxSum.

For each test, we check minimum sum if A[index] = a.
The minimum case would be A[index] is a peak in A.
It's arithmetic sequence on the left of A[index] with difference is 1.
It's also arithmetic sequence on the right of A[index] with difference is -1.

On the left, A[0] = max(a - index, 0),
On the right, A[n - 1] = max(a - ((n - 1) - index), 0),

The sum of arithmetic sequence {b, b+1, ....a},
equals to (a + b) * (a - b + 1) / 2.
*/
class Solution {
private:
    long getSum(int n, int index, int a) {
        int b = max(a - index, 0);
        long res = long(a + b) * (a - b + 1) / 2;  // the sum of first half of the array, 0 ~ index
        b = max(a - ((n - 1) - index), 0);
        res += long(a + b) * (a - b + 1) / 2;  // with the sum of the second half of the array, index ~ n - 1
        return res - a;                        // array[index] is counted twice
    }

public:
    int maxValue(int n, int index, int maxSum) {
        maxSum -= n;
        int left = 0, right = maxSum, mid;
        while (left < right) {
            mid = (left + right + 1) / 2;
            if (getSum(n, index, mid) <= maxSum)
                left = mid;
            else
                right = mid - 1;
        }
        return left + 1;
    }
};

// useful intro of BS,
// https://leetcode.com/discuss/general-discussion/786126/python-powerful-ultimate-binary-search-template-solved-many-problems