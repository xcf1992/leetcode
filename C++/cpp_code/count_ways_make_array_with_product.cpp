/*
1735. Count Ways to Make Array With Product
https://leetcode.com/problems/count-ways-to-make-array-with-product/

You are given a 2D integer array, queries.
For each queries[i], where queries[i] = [ni, ki],
find the number of different ways
you can place positive integers into an array of size ni
such that the product of the integers is ki.
As the number of ways may be too large,
the answer to the ith query is the number of ways modulo 109 + 7.

Return an integer array answer where answer.length == queries.length,
and answer[i] is the answer to the ith query.

Example 1:
Input: queries = [[2,6],[5,1],[73,660]]
Output: [4,1,50734910]
Explanation: Each query is independent.
[2,6]: There are 4 ways to fill an array of size 2 that multiply to 6: [1,6], [2,3], [3,2], [6,1].
[5,1]: There is 1 way to fill an array of size 5 that multiply to 1: [1,1,1,1,1].
[73,660]: There are 1050734917 ways to fill an array of size 73 that multiply to 660. 1050734917 modulo 109 + 7 =
50734910. Example 2: Input: queries = [[1,1],[2,2],[3,3],[4,4],[5,5]] Output: [1,2,3,10,5]

Constraints:
1 <= queries.length <= 104
1 <= ni, ki <= 104
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
#include <bitset>
using namespace std;

class Solution {
public:
    int spf[10001], mod = 1e9 + 7, MAXN = 10001;

    void sieve() {
        spf[1] = 1;  // spf[i] = smallest prime factor of i
        for (int i = 2; i < MAXN; i++)
            spf[i] = i;
        for (int i = 4; i < MAXN; i += 2)
            spf[i] = 2;
        for (int i = 3; i * i < MAXN; i++) {
            if (spf[i] == i) {
                // i is prime
                for (int j = i * i; j < 10001; j += i)  // mark all multiples of i
                    if (spf[j] == j)
                        spf[j] = i;
            }
        }
    }

    vector<int> get_factors(int x) {
        vector<int> res;
        unordered_map<int, int> frqs;  // a bit unnecessary but easier to code;
        while (x != 1) {
            frqs[spf[x]]++;  // frqs[i] = how many times the prime factor i occurs in x
            x = x / spf[x];
        }
        for (auto p : frqs)
            res.push_back(p.second);  // return the frequencies
        return res;
    }

    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        vector<int> res;
        sieve();
        long choose[10050][33] = {0};  // choose[i][j] = i Choose j
        for (int j = 0; j != 10050; ++j)
            choose[j][0] = 1;  // 1 way to choose 0 things
        for (int n = 1; n != 10050; ++n) {
            for (int r = 1; r != 33; ++r) {
                choose[n][r] = (choose[n - 1][r - 1] + choose[n - 1][r]) % mod;
            }
        }
        for (auto& q : queries) {
            int n = q[0], k = q[1];
            auto frqs = get_factors(k);
            long curr = 1;
            for (int f : frqs) {
                // each factor occurs f times, and these are indistinguishable but the buckets are distinguishable;
                // thus we use stars and bars formula
                curr = (curr * choose[n + f - 1][f]) % mod;
            }
            res.push_back(curr);
        }
        return res;
    }
};