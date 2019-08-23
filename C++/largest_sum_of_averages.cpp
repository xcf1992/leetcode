/*
813. Largest Sum of Averages
We partition a row of numbers A into at most K adjacent (non-empty) groups,
then our score is the preSum of the average of each group.
What is the largest score we can achieve?

Note that our partition must use every number in A, and that scores are not necessarily integers.

Example:
Input:
A = [9,1,2,3,9]
K = 3
Output: 20
Explanation:
The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
We could have also partitioned A into [9, 1], [2], [3, 9], for example.
That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.

Note:
1 <= A.length <= 100.
1 <= A[i] <= 10000.
1 <= K <= A.length.
Answers within 10^-6 of the correct answer will be accepted as correct.
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
#include <numeric>
using namespace std;
/*
Intuition

The best score partitioning A[i:] into at most K parts depends on answers to paritioning A[j:] (j > i) into less parts.
We can use dynamic programming as the states form a directed acyclic graph.

Algorithm

Let dp(i, k) be the best score partioning A[i:] into at most K parts.

If the first group we partition A[i:] into ends before j,
then our candidate partition has score average(i, j) + dp(j, k-1)),
where average(i, j) = (A[i] + A[i+1] + ... + A[j-1]) / (j - i) (floating point division).
We take the highest score of these, keeping in mind we don't necessarily need to partition - dp(i, k) can also be just average(i, N).

In total, our recursion in the general case is dp(i, k) = max(average(i, N), max_{j > i}(average(i, j) + dp(j, k-1))).

We can calculate average a little bit faster by remembering prefix preSums.
If P[x+1] = A[0] + A[1] + ... + A[x], then average(i, j) = (P[j] - P[i]) / (j - i).

Our implementation showcases a "bottom-up" style of dp. Here at loop number k in our outer-most loop,
dp[i] represents dp(i, k) from the discussion above, and we are calculating the next layer dp(i, k+1).
The end of our second loop for i = 0..N-1 represents finishing the calculation of the correct value for dp(i, t),
and the inner-most loop performs the calculation max_{j > i}(average(i, j) + dp(j, k)).
*/
class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        if (n == 0 or K == 0) {
            return 0;
        }

        vector<vector<double>> dp(K + 1, vector<double>(n, 0.0));
        vector<int> preSum;
        preSum.push_back(A[0]);
        for(int i = 1; i < n; i++) {
            preSum.push_back(A[i] + preSum.back());
        }

        // split the array into k groups, then there will have to be at least k numbers from A[0] ~ A[k-1]
        for (int k = 1; k <= K; k++) {
            for (int i = k - 1; i < n; i++) {
                if (k == 1) {
                    dp[k][i] = double (preSum[i]) / (i + 1);
                    continue;
                }
                // since we are going to split the first i number into k groups
                // we are going to search through based on dp[k - 1][j]
                // so split first j number into k - 1 groups, j < i
                // and number j + 1 to i as last group, total k groups
                // j should be at least k - 1 number, so the index j start from k - 2
                for (int j = k - 2; j < i; j++) {
                    dp[k][i] = max(dp[k][i], dp[k - 1][j] + double(preSum[i] - preSum[j]) / (i - j));
                }
            }
        }
        return dp[K][n - 1];
    }
};
