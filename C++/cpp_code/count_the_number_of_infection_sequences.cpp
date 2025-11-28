/*
https://leetcode.com/problems/count-the-number-of-infection-sequences/description/
2954. Count the Number of Infection Sequences

You are given an integer n and an array sick sorted in increasing order, representing positions of infected people in a
line of n people.

At each step, one uninfected person adjacent to an infected person gets infected. This process continues until everyone
is infected.

An infection sequence is the order in which uninfected people become infected, excluding those initially infected.

Return the number of different infection sequences possible, modulo 109+7.



Example 1:

Input: n = 5, sick = [0,4]

Output: 4

Explanation:

There is a total of 6 different sequences overall.

Valid infection sequences are [1,2,3], [1,3,2], [3,2,1] and [3,1,2].
[2,3,1] and [2,1,3] are not valid infection sequences because the person at index 2 cannot be infected at the first
step. Example 2:

Input: n = 4, sick = [1]

Output: 3

Explanation:

There is a total of 6 different sequences overall.

Valid infection sequences are [0,2,3], [2,0,3] and [2,3,0].
[3,2,0], [3,0,2], and [0,3,2] are not valid infection sequences because the infection starts at the person at index 1,
then the order of infection is 2, then 3, and hence 3 cannot be infected earlier than 2.


Constraints:

2 <= n <= 105
1 <= sick.length <= n - 1
0 <= sick[i] <= n - 1
sick is sorted in increasing order.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

constexpr int m = 100000;
long long fact[m + 1], inv_fact[m + 1], mod = 1000000007, init = 0;
class Solution {
public:
    int modPow(int x, int y, int mod) {
        if (y == 0)
            return 1;
        long p = modPow(x, y / 2, mod) % mod;
        p = (p * p) % mod;
        return y % 2 ? (p * x) % mod : p;
    }
    long long binom_coeff(int n, int k) {
        return max(1LL, fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod);
    }
    int numberOfSequence(int n, vector<int>& sick) {
        if (!init) {
            init = fact[0] = 1;
            for (int i = 1; i <= m; ++i)
                fact[i] = fact[i - 1] * i % mod;
            inv_fact[m] = modPow(fact[m], mod - 2, mod);
            for (int i = m - 1; i; --i)
                inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
        }
        long long res = 1;
        for (int i = 1; i < sick.size(); ++i) {
            int group = sick[i] - sick[i - 1] - 1;
            res = res * modPow(2, max(0, group - 1), mod) % mod;  // combine
            res = res * binom_coeff(sick[i] - i, group) % mod;    // interweave
        }
        return res * binom_coeff(n - sick.size(), n - sick.back() - 1) % mod;
    }
};
