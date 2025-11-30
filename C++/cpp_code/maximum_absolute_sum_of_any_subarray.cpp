/*
1749. Maximum Absolute Sum of Any Subarray
https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/

You are given an integer array nums.
The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr]
is abs(numsl + numsl+1 + ... + numsr-1 + numsr).

Return the maximum absolute sum of any (possibly empty) subarray of nums.
Note that abs(x) is defined as follows:
If x is a negative integer, then abs(x) = -x.
If x is a non-negative integer, then abs(x) = x.

Example 1:
Input: nums = [1,-3,2,3,-4]
Output: 5
Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.
Example 2:
Input: nums = [2,-5,1,-4,3,-2]
Output: 8
Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.

Constraints:
1 <= nums.length <= 105
-104 <= nums[i] <= 104
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
#include <climits>
#include <set>
#include <numeric>
#include <bitset>
using namespace std;
/*
Just find the maximum prefix sum and the minimum prefix sum.
return max - min.

Proof as homework,
Please think at least 10 minutes before you need a proof.

Proof
abs subarray sum
= one prefix sum - the other prefix sum
<= maximum prefix sum - minimum prefix sum

Suppose:
sum[0...a] is maximum, and it's value >= 0, because initial ma_sum = 0 and always takes max
sum[0...b] is minimum, and it's value <= 0, because initial mi_sum = 0 and always takes min

case 1: a is before b
[0,1,2,...a...b...end]
the sum [0...b] can be even smaller if it can exclude the sum from range [0...a]
so the largest different = abs(sum[0...b] - sum[0...a])

case 2: b is before a
[0,1,2,...b...a...end]
the sum [0...a] can be even greater if it can exclude the sum from range [0...b]
so the largest different = abs(sum[0...a] - sum[0...b])

both case we can use sum[0..a] - sum[0...b] since sum[0..a] >= 0, and sum[0...b] <= 0
*/
class Solution {
public:
    int maxAbsoluteSum(vector<int>& A) {
        int s = 0, mi = 0, ma = 0;
        for (int& a : A) {
            s += a;
            mi = min(mi, s);
            ma = max(ma, s);
        }
        return ma - mi;
    }
};