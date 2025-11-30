/*
903. Valid Permutations for DI Sequence

We are given S, a length n string of characters from the set {'D', 'I'}.
(These letters stand for "decreasing" and "increasing".)

A valid permutation is a permutation P[0], P[1], ..., P[n] of integers {0, 1, ..., n}, such that for all i:
If S[i] == 'D', then P[i] > P[i+1], and;
If S[i] == 'I', then P[i] < P[i+1].

How many valid permutations are there?
Since the answer may be large, return your answer modulo 10^9 + 7.

Example 1:
Input: "DID"
Output: 5
Explanation:
The 5 valid permutations of (0, 1, 2, 3) are:
(1, 0, 3, 2)
(2, 0, 3, 1)
(2, 1, 3, 0)
(3, 0, 2, 1)
(3, 1, 2, 0)

Note:
1 <= S.length <= 200
S consists only of characters from the set {'D', 'I'}.
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
#include <map>
#include <numeric>
using namespace std;
/*
dp[i][j] means the number of possible permutations of first i + 1 digits,
which also identifies first i letters in the DI string
where the i + 1th digit is j + 1th smallest in the rest of digits.

I take the example of S = "DID".
The permutation can start from 1, 2, 3, 4.
So dp[0][0] = dp[0][1] = dp[0][2] = dp[0][3] = 1.
In the parenthesis, I list all possible permutations.

We decrese from the first digit to the second,
the down arrow show the all possibile decresing pathes.

The same, cause we increase from the second digit to the third,
the up arrow show the all possibile increasing pathes.

dp[2][1] = 5, mean the number of permutations
where the third digitis the second smallest of the rest.
We have 413,314,214,423,324.
Fow example 413, where 2,3 are left and 3 the second smallest of them.

Explanation:
As shown in the diagram,
for "I", we calculate prefix sum of the array,
for "D", we calculate sufixsum of the array.

Time Complexity:
O(N^2)

============

Here is how to come up with this solution from the question.

Consider using dynamic programming to solve this problem.
Thus we need to find how to trans a problem to a sub-problem:
In a naive way, dp[i] : the total possible permutations count of first i+1 digits
how can dp[i] relate with dp[i-1]?
what is the relationship between them? we couldn't find. So try to add some parameter.

denote j as the i+1th digit is the j+1th smallest number in the rest not-yet-select digits.
so dp[i][j] : the total possible numbers of first i+1 digits,
where i+1th digit is the jth smallest number in the rest not-yet-select digits.

In such way, we can find out the relationship between problem and its sub-problem:
if we add a digit k as the first ith digit, and S[i]=='I',
we know that we can only add those digit which bigger than k as the first i+1th digit,
i.e., dp[i][j] can only form those dp[i][w], where w>=j.

example: S="DID", and we choose digit 2 as the first digit,
then when choosing the second digit,
we can only choose those bigger than 2 because we need "increase".
So we choose 3 and 4, noticing that 3 and 4 is the 2nd smallest and 3rd smallest in the rest non-select-yet digit
[1,3,4].

https://leetcode.com/problems/valid-permutations-for-di-sequence/discuss/168278/C%2B%2BJavaPython-DP-Solution-O(N2)
*/
/*
By using the rank j - there are j numbers less than the current number, we can calculate how many numbers for each case:

at position i: remaining numbers = n - i, by adding new number for this position -> remaining numbers = n-i-1
go down "D": dp[i][j] = accumulate dp[i-1][j greater than current j]
j goes down to accumulate from top to bottom: max j = n-i-1, min j = 0
go up "I": dp[i][j] = accumulate dp[i-1][j less than or equal to current j]
j goes up to accumulate from bottom to up: max j = n-i-1 (same as above), min j = 0.
*/
class Solution {
private:
    int mod = 1e9 + 7;

public:
    int numPermsDISequence(string S) {
        int n = S.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            dp[0][i] = 1;
        }

        for (int i = 0; i < n; i++) {
            int cur = 0;
            if (S[i] == 'I') {
                for (int j = 0; j < n - i; j++) {
                    cur = (cur + dp[i][j]) % mod;
                    dp[i + 1][j] = cur;
                }
            } else {
                for (int j = n - i - 1; j >= 0; j--) {
                    cur = (cur + dp[i][j + 1]) % mod;
                    dp[i + 1][j] = cur;
                }
            }
        }
        return dp[n][0];
    }
};

/*
Intuition
When writing the permutation P = P_0, P_1, ..., P_N from left to right,
we only care about the relative rank of the last element placed.
For example, if N = 5 (so that we have elements {0, 1, 2, 3, 4, 5}),
and our permutation starts 2, 3, 4,
then it is similar to a situation where we have placed ?, ?, 2
and the remaining elements are {0, 1, 3},
in terms of how many possibilities there are to place the remaining elements in a valid way.

To this end, let dp(i, j) be the number of ways to place every number up to and inlcuding P_i,
such that P_i when placed had relative rank j.
(Namely, there are j remaining numbers less than P_i.)

Algorithm
When placing P_i following a decreasing instruction S[i-1] == 'D',
we want P_{i-1} to have a higher value.

When placing P_i following an increasing instruction,
we want P_{i-1} to have a lower value.

It is relatively easy to deduce the recursion from this fact.

time complexity is O(n^3)
*/
class Solution1 {
private:
    int MOD = 1e9 + 7;

public:
    int numPermsDISequence(string S) {
        int n = S.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            dp[0][i] = 1;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (S[i - 1] == 'D') {
                    // it is decreasing, so previous number should be bigger than current number
                    // dp[i][j] means current number ranked j in 0 ... n, so privous number could be from j to i - 1
                    for (int k = j; k < i; k++) {
                        dp[i][j] += dp[i - 1][k];
                        dp[i][j] %= MOD;
                    }
                } else {
                    // it is decreasing, so previous number should be less than current number
                    // dp[i][j] means current number ranked j in 0 ... n, so privous number could be from 0 to j - 1
                    for (int k = 0; k < j; k++) {
                        dp[i][j] += dp[i - 1][k];
                        dp[i][j] %= MOD;
                    }
                }
            }
        }

        long result = 0;
        for (int x : dp[n]) {
            result += x;
            result %= MOD;
        }
        return result;
    }
};