/*
996. Number of Squareful Arrays

Given an array A of non-negative integers,
the array is squareful if for every pair of adjacent elements,
their sum is a perfect square.

Return the number of permutations of A that are squareful.
Two permutations A1 and A2 differ if and only if there is some index i such that A1[i] != A2[i].

Example 1:
Input: [1,17,8]
Output: 2
Explanation:
[1,8,17] and [17,8,1] are the valid permutations.

Example 2:
Input: [2,2,2]
Output: 1

Note:
1 <= A.length <= 12
0 <= A[i] <= 1e9
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
    // dfs O(n^n)
private:
    void dfs(int num, int length, map<int, int>& count, unordered_map<int, unordered_set<int>>& adj, int& result) {
        if (length == 0) {
            result += 1;
            return;
        }

        // cause we use set to store adjacent element, so every permutation will be count only once
        for (int next : adj[num])
            if (count[next] != 0) {
                count[next] -= 1;
                dfs(next, length - 1, count, adj, result);
                count[next] += 1;
            }
    }

public:
    int numSquarefulPerms(vector<int>& A) {
        map<int, int> count;
        for (int a : A) {
            count[a] += 1;
        }

        unordered_map<int, unordered_set<int>> adj;
        for (auto& i : count) {
            for (auto& j : count) {
                int n1 = i.first;
                int n2 = j.first;
                int root = sqrt(n1 + n2);
                if (root * root == n1 + n2) {
                    adj[n1].insert(n2);
                    adj[n2].insert(n1);
                }
            }
        }

        int result = 0;
        for (auto& it : count) {
            it.second -= 1;
            dfs(it.first, A.size() - 1, count, adj, result);
            it.second += 1;
        }
        return result;
    }
};

class Solution1 {
    // dfs with memo
    int n = 0;

    bool isPerfectSquare(int n1, int n2) {
        int root = sqrt(n1 + n2);
        return root * root == n1 + n2;
    }

    int dfs(int cur, int state, vector<vector<int>>& adj, vector<vector<int>>& dp) {
        if (state == (1 << n) - 1) {
            return 1;
        }

        if (dp[state][cur] != -1) {
            return dp[state][cur];
        }

        dp[state][cur] = 0;
        for (int nxt : adj[cur])
            if (((1 << nxt) & state) == 0) {
                dp[state][cur] += dfs(nxt, state | (1 << nxt), adj, dp);
            }
        return dp[state][cur];
    }

public:
    int numSquarefulPerms(vector<int>& A) {
        unordered_map<int, int> count;
        for (int a : A) {
            count[a] += 1;
        }

        n = A.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j)
                if (isPerfectSquare(A[i], A[j])) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
        }

        // dp[state][cur] means the result we have state with current visiting node cur
        vector<vector<int>> dp(1 << n, vector<int>(n, -1));
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += dfs(i, 1 << i, adj, dp);
        }

        vector<long> factorial(20);
        factorial[0] = 1;
        for (int i = 1; i < 20; ++i) {
            factorial[i] = i * factorial[i - 1];
        }
        for (auto& it : count)
            if (it.second > 1) {
                result /= factorial[it.second];
            }
        return result;
    }
};

class Solution2 {
    // dp O(n^2 * 2^n)
private:
    bool isPerfectSquare(int n1, int n2) {
        int root = sqrt(n1 + n2);
        return root * root == n1 + n2;
    }

public:
    int numSquarefulPerms(vector<int>& A) {
        int n = A.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j)
                if (isPerfectSquare(A[i], A[j])) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
        }

        vector<vector<int>> dp(1 << n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            dp[1 << i][i] = 1;
        }

        for (int state = 3; state < (1 << n); ++state) {
            for (int i = 0; i < n; ++i)
                if (state & (1 << i)) {
                    for (int j : adj[i])
                        if (state & (1 << j)) {
                            dp[state][i] += dp[state ^ (1 << i)][j];
                        }
                }
        }

        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += dp[(1 << n) - 1][i];
        }

        /* Divide out permutations of equal elements.*/
        for (int i = 0; i < n; i++) {
            int k = 1;
            for (int j = i + 1; j < n; j++) {
                if (A[i] == A[j]) {
                    k++;
                }
            }
            result /= k;
        }
        return result;
    }
};