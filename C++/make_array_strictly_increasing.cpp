/*
1187. Make Array Strictly Increasing
https://leetcode.com/problems/make-array-strictly-increasing/

Given two integer arrays arr1 and arr2,
return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.

In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
If there is no way to make arr1 strictly increasing, return -1.

Example 1:
Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
Output: 1
Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].

Example 2:
Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
Output: 2
Explanation: Replace 5 with 3 and then replace 3 with 4. arr1 = [1, 3, 4, 6, 7].

Example 3:
Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
Output: -1
Explanation: You can't make arr1 strictly increasing.

Constraints:
1 <= arr1.length, arr2.length <= 2000
0 <= arr1[i], arr2[i] <= 10^9
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

class Solution { // dfs with memo
private:
    unordered_map<int, unordered_map<int, int>> memo;

    int dfs(int cur, int prev, vector<int>& arr1, vector<int>& arr2) {
        if (cur >= arr1.size()) {
            return 0;
        }

        if (memo.find(cur) != memo.end() and memo[cur].find(prev) != memo[cur].end()) {
            return memo[cur][prev];
        }

        memo[cur][prev] = INT_MAX;
        if (arr1[cur] > prev) {
            memo[cur][prev] = min(memo[cur][prev], dfs(cur + 1, arr1[cur], arr1, arr2));
        }

        auto it = upper_bound(arr2.begin(), arr2.end(), prev);
        /*
        * we may still need to replace arr1[cur],
        * even when *it > arr1[cur] as it may happen we replaced arr1[cur - 1],
        * so now arr1[cur] is not big enough, case: [1,5,3,6,7], [1,3,4]
        */
        if (it != arr2.end()) {
            int move = dfs(cur + 1, *it, arr1, arr2);
            if (move != INT_MAX) {
                memo[cur][prev] = min(memo[cur][prev], 1 + move);
            }
        }
        return memo[cur][prev];
    }
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) { // dfs with memo
        sort(arr2.begin(), arr2.end());
        int result = dfs(0, INT_MIN, arr1, arr2);
        return result == INT_MAX ? -1 : result;
    }
};

class Solution1 { // TLE
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        map<int, int> count;
        for (int num : arr2) {
            count[num] += 1;
        }

        vector<int> replacement;
        for (auto& it : count) {
            replacement.push_back(it.first);
        }

        int n1 = arr1.size();
        int n2 = replacement.size();
        vector<vector<int>> dp(n1, vector<int>(n2 + 1, INT_MAX));
        dp[0][0] = 0;
        for (int j = 1; j <= n2; ++j) {
            dp[0][j] = 1;
        }

        for (int i = 1; i < n1; ++i) {
            for (int j = 0; j <= n2; ++j) if (dp[i - 1][j] != INT_MAX) {
                int previous = j == 0 ? arr1[i - 1] : replacement[j - 1];
                if (arr1[i] > previous) {
                    dp[i][0] = min(dp[i][0], dp[i - 1][j]);
                }
                for (int k = j + 1; k <= n2; ++k) if (replacement[k - 1] > previous) {
                    dp[i][k] = min(dp[i][k], dp[i - 1][j] + 1);
                }
            }
        }

        int result = INT_MAX;
        for (int j = 0; j <= n2; ++j) {
            result = min(result, dp[n1 - 1][j]);
        }
        return result == INT_MAX ? -1 : result;
    }
};
