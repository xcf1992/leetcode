/*
https://leetcode.com/problems/sum-of-total-strength-of-wizards/description/
2281. Sum of Total Strength of Wizards

As the ruler of a kingdom, you have an army of wizards at your command.

You are given a 0-indexed integer array strength, where strength[i] denotes the strength of the ith wizard. For a
contiguous group of wizards (i.e. the wizards' strengths form a subarray of strength), the total strength is defined as
the product of the following two values:

The strength of the weakest wizard in the group.
The total of all the individual strengths of the wizards in the group.
Return the sum of the total strengths of all contiguous groups of wizards. Since the answer may be very large, return it
modulo 109 + 7.

A subarray is a contiguous non-empty sequence of elements within an array.



Example 1:

Input: strength = [1,3,1,2]
Output: 44
Explanation: The following are all the contiguous groups of wizards:
- [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
- [3] from [1,3,1,2] has a total strength of min([3]) * sum([3]) = 3 * 3 = 9
- [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
- [2] from [1,3,1,2] has a total strength of min([2]) * sum([2]) = 2 * 2 = 4
- [1,3] from [1,3,1,2] has a total strength of min([1,3]) * sum([1,3]) = 1 * 4 = 4
- [3,1] from [1,3,1,2] has a total strength of min([3,1]) * sum([3,1]) = 1 * 4 = 4
- [1,2] from [1,3,1,2] has a total strength of min([1,2]) * sum([1,2]) = 1 * 3 = 3
- [1,3,1] from [1,3,1,2] has a total strength of min([1,3,1]) * sum([1,3,1]) = 1 * 5 = 5
- [3,1,2] from [1,3,1,2] has a total strength of min([3,1,2]) * sum([3,1,2]) = 1 * 6 = 6
- [1,3,1,2] from [1,3,1,2] has a total strength of min([1,3,1,2]) * sum([1,3,1,2]) = 1 * 7 = 7
The sum of all the total strengths is 1 + 9 + 1 + 4 + 4 + 4 + 3 + 5 + 6 + 7 = 44.
Example 2:

Input: strength = [5,4,6]
Output: 213
Explanation: The following are all the contiguous groups of wizards:
- [5] from [5,4,6] has a total strength of min([5]) * sum([5]) = 5 * 5 = 25
- [4] from [5,4,6] has a total strength of min([4]) * sum([4]) = 4 * 4 = 16
- [6] from [5,4,6] has a total strength of min([6]) * sum([6]) = 6 * 6 = 36
- [5,4] from [5,4,6] has a total strength of min([5,4]) * sum([5,4]) = 4 * 9 = 36
- [4,6] from [5,4,6] has a total strength of min([4,6]) * sum([4,6]) = 4 * 10 = 40
- [5,4,6] from [5,4,6] has a total strength of min([5,4,6]) * sum([5,4,6]) = 4 * 15 = 60
The sum of all the total strengths is 25 + 16 + 36 + 36 + 40 + 60 = 213.


Constraints:

1 <= strength.length <= 105
1 <= strength[i] <= 109
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
#include <climits>
using namespace std;

/*
How do we get the "sum of all subarrays including strength[i] in range (left, right)"?
Let's list the indices:
...left-1, left, left + 1, left + 2, ... i-1, i, i+1, ... right-1, right, right+1...

Let prefix[i] be the prefix sum of first i elements in strength.

The sum of subarrays including i are:

the subarrays that start with left+1:
sum(left+1, ... i) = prefix[i + 1] - prefix[left + 1]
sum(left+1, ... i+1) = prefix[i + 2] - prefix[left + 1]
...
sum(left+1, ... right-1) = prefix[right] - prefix[left + 1]
the subarrays that start with left+2:
sum(left+2, ... i) = prefix[i + 1] - prefix[left + 2]
sum(left+2, ... i+1) = prefix[i + 2] - prefix[left + 2]
...
sum(left+2, ... right-1) = prefix[right] - prefix[left + 2]
...

the subarrays that start with i:
sum(i, ... i) = prefix[i + 1] - prefix[i]
sum(i, ... i+1) = prefix[i + 2] - prefix[i]
...
sum(i, ... right-1) = prefix[right] - prefix[i]
Then we combine all above terms, we have:

positive parts:
(prefix[i + 1] + prefix[i + 2] + ... + prefix[right]) * (i - left)
negative parts:
(prefix[left + 1] + prefix[left + 2] + ... + prefix[i]) * (right - i)
The range sum of prefix can be optimized by pre-compute prefix-sum of prefix.
 */
class Solution {
private:
    long long MOD = 1e9 + 7;

public:
    int totalStrength(vector<int>& strength) {
        const int n = strength.size();
        // sum of first k elements
        vector<long long> prefix(n + 1, 0L);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = (prefix[i] + strength[i]) % MOD;
        }

        // sum of first k prefix
        vector<long long> prefix_sum(n + 2, 0L);
        for (int i = 0; i <= n; ++i) {
            prefix_sum[i + 1] = (prefix_sum[i] + prefix[i]) % MOD;
        }

        // first index on the left < current st
        vector<int> pre_less_idx(n, -1);

        // mono increase
        vector<int> max_stk;
        for (int i = 0; i < n; ++i) {
            while (!max_stk.empty() && strength[max_stk.back()] >= strength[i]) {
                max_stk.pop_back();
            }
            pre_less_idx[i] = max_stk.empty() ? -1 : max_stk.back();
            max_stk.push_back(i);
        }

        // first index on the right <= current st
        vector<int> nxt_less_idx(n, n);
        max_stk.clear();
        for (int i = n - 1; i >= 0; --i) {
            while (!max_stk.empty() && strength[max_stk.back()] > strength[i]) {
                max_stk.pop_back();
            }
            nxt_less_idx[i] = max_stk.empty() ? n : max_stk.back();
            max_stk.push_back(i);
        }

        long long res = 0;
        for (int i = 0; i < n; ++i) {
            res += ((prefix_sum[nxt_less_idx[i] + 1] - prefix_sum[i + 1]) * (i - pre_less_idx[i]) % MOD + MOD * 2 -
                    (prefix_sum[i + 1] - prefix_sum[pre_less_idx[i] + 1]) * (nxt_less_idx[i] - i) % MOD) %
                   MOD * strength[i] % MOD;
            res %= MOD;
        }
        return (int)res;
    }
};
