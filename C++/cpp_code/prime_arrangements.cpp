/*
1175. Prime Arrangements
Return the number of permutations of 1 to n so that prime numbers are at prime indices (1-indexed.)

(Recall that an integer is prime if and only if it is greater than 1,
and cannot be written as a product of two positive integers both smaller than it.)

Since the answer may be large, return the answer modulo 10^9 + 7.

Example 1:

Input: n = 5
Output: 12
Explanation: For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is not because the prime number 5 is at
index 1. Example 2:

Input: n = 100
Output: 682289015


Constraints:

1 <= n <= 100
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
#include <climits>
#include <set>
using namespace std;

class Solution {
private:
    int MOD = 1e9 + 7;

    int getPrimeCount(int n) {
        if (n <= 2) {
            return n - 1;
        }

        vector<bool> isPrime(n + 1, true);
        isPrime[1] = false;
        for (int i = 2; i <= n; ++i)
            if (isPrime[i]) {
                for (int j = i; i * j <= n; ++j) {
                    isPrime[i * j] = false;
                }
            }

        int result = 0;
        for (int i = 1; i <= n; ++i)
            if (isPrime[i]) {
                result += 1;
            }
        return result;
    }

    int getPerm(int num) {
        if (num <= 1) {
            return 1;
        }

        long result = 1;
        for (int i = 1; i <= num; ++i) {
            result = result * i % MOD;
        }
        return result;
    }

public:
    int numPrimeArrangements(int n) {
        int k = getPrimeCount(n);
        long k1 = getPerm(k) % MOD;
        long k2 = getPerm(n - k) % MOD;
        long result = k1 * k2;
        return result % MOD;
    }
};