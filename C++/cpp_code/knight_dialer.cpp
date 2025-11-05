/*
935. Knight Dialer
https://leetcode.com/problems/knight-dialer/

A chess knight can move as indicated in the chess diagram below:

This time, we place our chess knight on any numbered key of a phone pad (indicated above),
and the knight makes N-1 hops.
Each hop must be from one key to another numbered key.

Each time it lands on a key (including the initial placement of the knight),
it presses the number of that key, pressing N digits total.

How many distinct numbers can you dial in this manner?
Since the answer may be large, output the answer modulo 10^9 + 7.

Example 1:
Input: 1
Output: 10

Example 2:
Input: 2
Output: 20

Example 3:
Input: 3
Output: 46

Note:
1 <= N <= 5000
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

class Solution {
private:
    long MOD = 1e9 + 7;

public:
    int knightDialer(int N) {
        vector<vector<int> > next({
            {4, 6},
            {8, 6},
            {7, 9},
            {4, 8},
            {0, 3, 9},
            {},
            {0, 1, 7},
            {2, 6},
            {1, 3},
            {2, 4}
        });
        vector<vector<int> > dp(N + 1, vector<int>(10, 0));
        for (int i = 0; i < 10; i++) {
            dp[1][i] = 1;
        }

        for (int len = 2; len <= N; ++len) {
            for (int digit = 0; digit < 10; ++digit) {
                for (int num: next[digit]) {
                    dp[len][digit] = (dp[len][digit] + dp[len - 1][num]) % MOD;
                }
            }
        }

        int result = 0;
        for (int i = 0; i < 10; ++i) {
            result = (result + dp[N][i]) % MOD;
        }
        return result;
    }
};

class Solution1 {
private:
    long MOD = 1e9 + 7;

    long count(int curDigit, int length, int N, vector<vector<int> > &next,
               unordered_map<int, unordered_map<int, long> > &mem) {
        if (length == N) {
            return 1;
        }

        if (mem.find(curDigit) != mem.end()) {
            if (mem[curDigit].find(length) != mem[curDigit].end()) {
                return mem[curDigit][length];
            }
        }
        int ans = 0;
        for (int nextDigit: next[curDigit]) {
            ans += count(nextDigit, length + 1, N, next, mem);
            ans %= MOD;
        }
        mem[curDigit][length] = ans;
        return ans;
    }

public:
    int knightDialer(int N) {
        vector<vector<int> > next({
            {4, 6},
            {8, 6},
            {7, 9},
            {4, 8},
            {0, 3, 9},
            {},
            {0, 1, 7},
            {2, 6},
            {1, 3},
            {2, 4}
        });

        unordered_map<int, unordered_map<int, long> > mem;
        long result = 0;
        for (int i = 0; i <= 9; i++) {
            result += count(i, 1, N, next, mem);
            result %= MOD;
        }
        return (int) result;
    }
};

// Time limit exceed
class Solution2 {
private:
    long MOD = 1e9 + 7;

    long count(int curDigit, int length, int N, vector<vector<int> > &next) {
        if (length == N) {
            return 1;
        }
        int ans = 0;
        for (int nextDigit: next[curDigit]) {
            ans += count(nextDigit, length + 1, N, next);
            ans %= MOD;
        }
        return ans;
    }

public:
    int knightDialer(int N) {
        vector<vector<int> > next({
            {4, 6},
            {8, 6},
            {7, 9},
            {4, 8},
            {0, 3, 9},
            {},
            {0, 1, 7},
            {2, 6},
            {1, 3},
            {2, 4}
        });
        long result = 0;
        for (int i = 0; i <= 9; i++) {
            result += count(i, 1, N, next);
            result %= MOD;
        }
        return (int) result;
    }
};