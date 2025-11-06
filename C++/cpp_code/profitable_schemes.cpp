/*
879. Profitable Schemes

There are G people in a gang, and a list of various crimes they could commit.
The i-th crime generates a profit[i] and requires group[i] gang members to participate.

If a gang member participates in one crime, that member can't participate in another crime.

Let's call a profitable scheme any subset of these crimes that generates at least P profit,
and the total number of gang members participating in that subset of crimes is at most G.

How many schemes can be chosen?
Since the answer may be very large,
return it modulo 10^9 + 7.

Example 1:
Input: G = 5, P = 3, group = [2,2], profit = [2,3]
Output: 2
Explanation:
To make a profit of at least 3, the gang could either commit crimes 0 and 1, or just crime 1.
In total, there are 2 schemes.

Example 2:
Input: G = 10, P = 5, group = [2,3,5], profit = [6,7,8]
Output: 7
Explanation:
To make a profit of at least 5, the gang could commit any crimes, as long as they commit one.
There are 7 possible schemes: (0), (1), (2), (0,1), (0,2), (1,2), and (0,1,2).

Note:
1 <= G <= 100
0 <= P <= 100
1 <= group[i] <= 100
0 <= profit[i] <= 100
1 <= group.length = profit.length <= 100
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
Well, it is a Knapsack problem and my first intuition is dp.

dp[i][j] means the count of schemes with i profit and j members.

The dp equation is simple here:
dp[i + p][j + g] += dp[i][j]) if i + p < P
dp[P][j + g] += dp[i][j]) if i + p >= P

Don't forget to take care of overflow.

For each pair (p, g) of (profit, group), I update the count in dp.

Time Complexity:
O(NPG)
*/
class Solution2 {
private:
    int mod = 1e9 + 7;

public:
    int profitableSchemes(int G, int P, vector<int> group, vector<int> profit) {
        vector<vector<int>> dp(P + 1, vector<int>(G + 1, 0));
        dp[0][0] = 1;
        for (int k = 0; k < group.size(); k++) {
            int g = group[k];
            int p = profit[k];
            for (int i = P; i >= 0; i--) {
                for (int j = G - g; j >= 0; j--) {
                    dp[min(i + p, P)][j + g] += dp[i][j];
                    dp[min(i + p, P)][j + g] %= mod;
                }
            }
        }

        int result = 0;
        for (int count : dp[P]) {
            result = (result + count) % mod;
        }
        return result;
    }
};

/*
Because all k dimension only depends on k - 1 dimension, so we can improve it to 2D array which only has i and j
dimension. Just be careful about that i and j should be decrease, in order to get correct old k - 1 dimension value.
*/
class Solution {
private:
    int mod = 1e9 + 7;

public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int n = group.size();
        vector<vector<int>> dp(P + 1, vector<int>(G + 1, 0));
        // when there is 0 crime, 0 scheme existed for any profit > 0 or group > 0
        dp[0][0] = 1;
        for (int i = 0; i < n; ++i) {
            int p = profit[i];
            int g = group[i];
            /*
             * cause we reuse the same matrix while loop through differernt crime,
             * we will have to iterate from the back of the matrix,
             * so we do not update previous value, while we still needed
             */
            for (int j = P; j >= 0; j--) {
                for (int k = G; k >= g; k--) {
                    dp[j][k] += dp[max(0, j - p)][k - g];
                    dp[j][k] %= mod;
                }
            }
        }

        long result = 0;
        for (int i = 0; i <= G; i++) {
            result += dp[P][i];
            result %= mod;
        }
        return result;
    }
};

/*
dp[k][i][j] means for first k crime with i members and at least j profit, what is total schemes can be chosen.

And we need this Math.max(0, j - p), because this is for at least j profit.

dp[k][i][j] = dp[k - 1][i][j] + dp[k - 1][i - current group][Math.max(0, j - current profit)]
*/
class Solution1 {
private:
    int mod = 1e9 + 7;

public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int n = group.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(P + 1, vector<int>(G + 1, 0)));
        // when there is 0 crime, 0 scheme existed for any profit > 0 or group > 0
        dp[0][0][0] = 1;
        for (int i = 1; i <= n; i++) {
            int p = profit[i - 1];
            int g = group[i - 1];
            for (int j = 0; j <= P; j++) {
                for (int k = 0; k <= G; k++) {
                    long count = dp[i - 1][j][k];
                    if (k >= g) {
                        count += dp[i - 1][max(0, j - p)][k - g];
                    }
                    dp[i][j][k] = count % mod;
                }
            }
        }

        long result = 0;
        for (int i = 0; i <= G; i++) {
            result += dp[n][P][i];
            result %= mod;
        }
        return result;
    }
};

/*
 dp[i][j] means the count of schemes with i profit and j members.
*/
class Solution3 {
private:
    int mod = 1e9 + 7;

    int dfs(int g, int p, int index, vector<int>& group, vector<int>& profit, vector<vector<vector<int>>>& memo) {
        if (index < 0) {
            return p <= 0 ? 1 : 0;
        }

        if (memo[index][p][g] != -1) {
            return memo[index][p][g];
        }

        long result = dfs(g, p, index - 1, group, profit, memo);
        if (g >= group[index]) {
            result += dfs(g - group[index], max(0, p - profit[index]), index - 1, group, profit, memo);
        }
        result %= mod;
        memo[index][p][g] = result;
        return result;
    }

public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int n = group.size();
        vector<vector<vector<int>>> memo(n + 1, vector<vector<int>>(P + 1, vector<int>(G + 1, -1)));
        return dfs(G, P, n - 1, group, profit, memo);
    }
};