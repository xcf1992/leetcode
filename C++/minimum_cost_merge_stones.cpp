/*
 1000. Minimum Cost to Merge Stones
 There are N piles of stones arranged in a row.
 The i-th pile has stones[i] stones.

 A move consists of merging exactly K consecutive piles into one pile,
 and the cost of this move is equal to the total number of stones in these K piles.

 Find the minimum cost to merge all piles of stones into one pile.
 If it is impossible, return -1.

 Example 1:

 Input: stones = [3,2,4,1], K = 2
 Output: 20
 Explanation:
 We start with [3, 2, 4, 1].
 We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
 We merge [4, 1] for a cost of 5, and we are left with [5, 5].
 We merge [5, 5] for a cost of 10, and we are left with [10].
 The total cost was 20, and this is the minimum possible.
 Example 2:

 Input: stones = [3,2,4,1], K = 3
 Output: -1
 Explanation: After any merge operation, there are 2 piles left, and we can't merge anymore.  So the task is impossible.
 Example 3:

 Input: stones = [3,5,1,2,6], K = 3
 Output: 25
 Explanation:
 We start with [3, 5, 1, 2, 6].
 We merge [5, 1, 2] for a cost of 8, and we are left with [3, 8, 6].
 We merge [3, 8, 6] for a cost of 17, and we are left with [17].
 The total cost was 25, and this is the minimum possible.


 Note:

 1 <= stones.length <= 30
 2 <= K <= 30
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
suppose F(n) is total number of n-n time merge
we know :
F(n-1) = F(n)-K+1
F(n-2) = F(n-1)-K+1
...
finaly we have F(1) = F(n) - m(K-1)
if we merge end . F(1) = 1
so,We have 1 = n -m(K-1) ----> so we have
(n-1)%(k-1) == remain

 During interview, this might be our first question, the follow-up may ask us what if we can merge x consecutive piles?
 Just like original problem.
 Now our sub problem becomes: we need to know the minimum cost of merging left part to x - 1 piles and right part to 1 pile.
 Our state has one more information to know, how many piles. So we add the field to our dp array.

 State: Minimum cost merging piles from i to j to k pile.

 Function: dp[i][j][k] = min(sum[i][j] + dp[i][t][k - 1] + dp[t + 1][j][1])
 (i <= t < j && dp[i][t][k - 1] != max && dp[t+1][j][1] != max)

 Init: dp[i][i][1] = 0 (Already a pile) others = max

 Answer: dp[1][len][1] (len is the stones number)

 Time Complexity: O(n^3 * K) (n is the number of stone)

 Similar problem include 312. Burst Balloons.
 They are all dynamic programming problem related to interval.

 Q: Why mid jump at step K - 1
 A: We can merge K piles into one pile,
 we can't merge K + 1 piles into one pile.
 We can merge K + K - 1 piles into one pile,
 We can merge K + (K - 1) * steps piles into one pile.
 */
class Solution {
public:
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();
        if ((n - 1) % (K - 1) != 0) {
            return -1;
        }

        vector<int> prefix(n + 1);
        for (int i = 0; i <  n; i++) {
            prefix[i + 1] = prefix[i] + stones[i];
        }

        vector<vector<int>> dp(n, vector<int>(n));
        for (int m = K; m <= n; ++m) {
            for (int i = 0; i + m <= n; ++i) {
                int j = i + m - 1;
                dp[i][j] = INT_MAX;
                for (int mid = i; mid < j; mid += K - 1) {
                    dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid + 1][j]);
                }
                if ((j - i) % (K - 1) == 0) {
                    dp[i][j] += prefix[j + 1] - prefix[i];
                }
            }
        }
        return dp[0][n - 1];
    }
};

class Solution1 {
public:
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();
        vector<int> sum(n, 0);
        for (int i = 0; i < n;i++) {
            sum[i] = i > 0 ? sum[i - 1] + stones[i] : 0;
        }

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(K + 1, INT_MAX)));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                for(int k = 1; k <= K; k++) {
                    if (j - i + 1 == k) {
                        dp[i][j][k] = 0; // it is already k piles so we do not need to do merge at all
                    }
                }
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                for (int k = 1; k <= K; k++) {
                    for (int m = i; m < j; m++) {
                        if (k > 1) {
                            if (dp[i][m][1] == INT_MAX or dp[m + 1][j][k - 1] == INT_MAX) {
                                continue;
                            }
                            dp[i][j][k] = min(dp[i][j][k], dp[i][m][1] + dp[m + 1][j][k - 1]);
                        }
                        else {
                            if (dp[i][m][1] == INT_MAX or dp[m + 1][j][K - 1] == INT_MAX) {
                                continue;
                            }
                            dp[i][j][1] = min(dp[i][j][k], dp[i][m][1] + dp[m + 1][j][K - 1] + sum[j] - sum[i] + stones[i]);
                        }
                    }

                }
            }
        }
        return dp[0][n - 1][1] == INT_MAX ? -1 : dp[0][n - 1][1];
    }
};

/*
 Let's first think this problem in a simple way, what if we can only merge 2 adjacent piles into one pile?

 For given example [3,2,4,1], we will normally think this as a greedy problem, we always merge two relatively small piles.
 [[3, 2], 4, 1] -> [5, [4, 1]] -> [5, 5] -> [10](cost: 20).

 While one counterexample is [6,4,4,6],
 if we merge greedily, [6, [4, 4], 6] -> [[6, 8], 6] -> [14, 6] -> [20] (cost: 42),
 while the optimal way is [[6, 4], 4, 6] -> [10, [4, 6]] -> [10, 10] -> [20] (cost:40).

 What if we think this problem reversely, which two piles should we merge at the last step?

 We don't know which two piles to merge for now, but we can know the cost of that step, which is the sum of that two piles.
 [3 | 2, 4, 1]
 3 + 7 = 10
 [3 , 2 | 4, 1]
 5 + 5 = 10
 [3 , 2, 4 | 1]
 9 + 1 = 10
 No matter how to split the two piles, the sum is always the sum of the two piles.

 Now the only thing that matters is how to get the minimum cost to split to two piles.
 So we need to know the minimum cost of merging left part to 1 pile,
 and minimum cost of merging right part to 1 pile, this is a typical sub problem.

 State: Minimum cost merging piles from i to j to 1 pile.

 Function: dp[i][j] = min(sum[i][j] + dp[i][k] + dp[k + 1][j]) (i <= k < j)

 Init: dp[i][i] = 0 (Already a pile)

 Answer: dp[1][len] (len is the stones number)
 */
class Solution2 { // solution when K == 2
public:
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();
        if (n <= 1) {
            return 0;
        }

        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            prefixSum[i] = prefixSum[i - 1] + stones[i - 1];
        }

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
        for (int i = 1; i <= n; i++) {
            dp[i][i] = 0;
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 1; i <= n - len + 1; i++) {
                int j = i + len - 1;
                int sum = prefixSum[j] - prefixSum[i - 1];
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], sum + dp[i][k] + dp[k + 1][j]);
                }
            }
        }
        return dp[1][n];
    }
};
