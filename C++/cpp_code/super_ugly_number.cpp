/*
313. Super Ugly Number

Write a program to find the nth super ugly number.
Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.

Example:
Input: n = 12, primes = [2,7,13,19]
Output: 32
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
             super ugly numbers given primes = [2,7,13,19] of size 4.

Note:
1 is a super ugly number for any given primes.
The given numbers in primes are in ascending order.
0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
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
using namespace std;

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int> &primes) {
        vector<int> result;
        result.push_back(1);

        int k = primes.size();
        vector<int> idxs(k, 0);

        while (result.size() < n) {
            int nextNum = result[idxs[0]] * primes[0];
            for (int i = 1; i < k; i++) {
                nextNum = min(nextNum, result[idxs[i]] * primes[i]);
            }

            result.push_back(nextNum);
            for (int i = 0; i < k; i++) {
                if (nextNum == result[idxs[i]] * primes[i]) {
                    idxs[i]++;
                }
            }
        }
        return result.back();
    }
};