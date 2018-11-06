/*
 We are given S, a length n string of characters from the set {'D', 'I'}. (These letters stand for "decreasing" and "increasing".)
 
 A valid permutation is a permutation P[0], P[1], ..., P[n] of integers {0, 1, ..., n}, such that for all i:
 
 If S[i] == 'D', then P[i] > P[i+1], and;
 If S[i] == 'I', then P[i] < P[i+1].
 How many valid permutations are there?  Since the answer may be large, return your answer modulo 10^9 + 7.
 
 
 
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
#include <stdio.h>
#include <map>
#include <numeric>
using namespace std;

/*
 dp[i][j] means the number of possible permutations of first i + 1 digits,
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
            }
            else {
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
 When writing the permutation P = P_0, P_1, ..., P_N from left to right, we only care about the relative rank of the last element placed. For example, if N = 5 (so that we have elements {0, 1, 2, 3, 4, 5}), and our permutation starts 2, 3, 4, then it is similar to a situation where we have placed ?, ?, 2 and the remaining elements are {0, 1, 3}, in terms of how many possibilities there are to place the remaining elements in a valid way.
 To this end, let dp(i, j) be the number of ways to place every number up to and inlcuding P_i, such that P_i when placed had relative rank j. (Namely, there are j remaining numbers less than P_i.)
 
 Algorithm
 When placing P_i following a decreasing instruction S[i-1] == 'D', we want P_{i-1} to have a higher value. When placing P_i following an increasing instruction, we want P_{i-1} to have a lower value. It is relatively easy to deduce the recursion from this fact.
 
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
                }
                else {
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
