/*
 887. Super Egg Drop
 You are given K eggs, and you have access to a building with N floors from 1 to N.

 Each egg is identical in function, and if an egg breaks, you cannot drop it again.

 You know that there exists a floor F with 0 <= F <= N such that any egg dropped at a floor higher than F will break, and any egg dropped at or below floor F will not break.

 Each move, you may take an egg (if you have an unbroken one) and drop it from any floor X (with 1 <= X <= N).

 Your goal is to know with certainty what the value of F is.

 What is the minimum number of moves that you need to know with certainty what F is, regardless of the initial value of F?


 Example 1:

 Input: K = 1, N = 2
 Output: 2
 Explanation:
 Drop the egg from floor 1.  If it breaks, we know with certainty that F = 0.
 Otherwise, drop the egg from floor 2.  If it breaks, we know with certainty that F = 1.
 If it didn't break, then we know with certainty F = 2.
 Hence, we needed 2 moves in the worst case to know what F is with certainty.
 Example 2:

 Input: K = 2, N = 6
 Output: 3
 Example 3:

 Input: K = 3, N = 14
 Output: 4


 Note:

 1 <= K <= 100
 1 <= N <= 10000
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
 It's natural to attempt dynamic programming,
 as we encounter similar subproblems.

 Our state is (K, N): K eggs and N floors left.

 When we drop an egg from floor X,
 it either survives and we have state (K, N-X),
 or it breaks and we have state (K-1, X-1).

 where dp[K][N] = 1 + max(dp[K - 1][i - 1], dp[K][N - i]) for i in 1...N.

 However this idea is very brute force,
 for the reason that you check all possiblity.
 This approach would lead to a O(KN^2)

 The number of eggs will determine the strategy you can use to check the floors.
 if you have only one egg,
 you need to use the most conservative strategy.
 which is check from level 1;
 and move 1 level up each time,
 then when the egg broke,
 you can determine the target level.
 Otherwise if the egg broke, you will have no egg to perform another test.

 If you have more eggs,
 you can try some other aggressive strategy;
 which will probably decease the number of moves needed

 A move essentially is dropping an egg and it either breaks or doesn't break.
 Case A: The egg breaks and now you have spent 1 move (M=M-1)
 and also lost 1 egg (K=K-1).
 You can still check dp[M-1][K-1] floors,
 with your remaining eggs and moves.

 Case B: The egg remains and you only loose one move (M=M-1).
 You can still check dp[M-1][K] floors.
 Additionally you just checked a floor by dropping the egg from it.

 Therefore dp[M][K] = dp[M - 1][k - 1] + dp[M - 1][K] + 1

 As you can see we can easily calculate how many floors we can check in M moves if we know how many floors we can check in M-1 moves.

 The basic idea is when the egg break,
 we will search dp[m - 1][k - 1] below current level and
 when the egg not break we will search dp[m - 1][k] above current level.
 That's the reason why we will combine them together but not only pick the smaller one.
 Hope my explanation can help you understand Lee's solution better.
 */

/*
So I consider this problem in a different way:
dp[M][K]means that, given K eggs and M moves,
what is the maximum number of floor that we can check.

The dp equation is:
dp[m][k] = dp[m - 1][k - 1] + dp[m - 1][k] + 1,
which means we take 1 move to a floor,
if egg breaks, then we can check dp[m - 1][k - 1] floors.
if egg doesn't breaks, then we can check dp[m - 1][k - 1] floors.

dp[m][k] is similar to the number of combinations and it increase exponentially to N

The dp equation is:
dp[m][k] = dp[m - 1][k - 1] + dp[m - 1][k] + 1,
assume, dp[m-1][k-1] = n0, dp[m-1][k] = n1
the first floor to check is n0+1.
if egg breaks, F must be in [1,n0] floors, we can use m-1 moves and k-1 eggs to find out F is which one.
if egg doesn't breaks and F is in [n0+2, n0+n1+1] floors, we can use m-1 moves and k eggs to find out F is which one.
So, with m moves and k eggs, we can find out F in n0+n1+1 floors, whichever F is.
*/
class Solution {
public:
    int superEggDrop(int K, int N) {
        vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));
        int m = 0;
        while (dp[m][K] < N) {
            m += 1;
            for (int k = 1; k <= K; k++) {
                dp[m][k] = dp[m - 1][k - 1] + (dp[m - 1][k] + 1);
            }
        }
        return m;
    }
};

/*
We can easily come up with an O(KN^2) DP solution, where dp[k][n] = min(1 + max(dp[k - 1][i - 1], dp[k][n - i])) i = 1...n
In this implementation, we use recursion to simulate each move.
But it runs TLE.
*/
class Solution1 {
private:
    int helper(int K, int N, vector<vector<int>>& memo) {
        if (N <= 1) {
            return N;
        }
        if (K == 1) {
            return N;
        }
        if (memo[K][N] > 0) {
            return memo[K][N];
        }

        memo[K][N] = N;
        for (int i = 1; i <= N; i++) {
            int left = helper(K - 1, i - 1, memo);
            int right = helper(K, N - i, memo);
            memo[K][N] = min(memo[K][N], max(left, right) + 1);
        }
        return memo[K][N];
    }
public:
    int superEggDrop(int K, int N) {
        vector<vector<int>> memo(K + 1, vector<int>(N + 1, 0));
        return helper(K, N, memo);
    }
};
