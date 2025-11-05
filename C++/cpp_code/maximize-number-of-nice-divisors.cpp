/*
1808. Maximize Number of Nice Divisors
https://leetcode.com/problems/maximize-number-of-nice-divisors/

You are given a positive integer primeFactors.
You are asked to construct a positive integer n that satisfies the following conditions:

The number of prime factors of n (not necessarily distinct) is at most primeFactors.
The number of nice divisors of n is maximized.
Note that a divisor of n is nice if it is divisible by every prime factor of n.
For example, if n = 12, then its prime factors are [2,2,3],
then 6 and 12 are nice divisors, while 3 and 4 are not.

Return the number of nice divisors of n. Since that number can be too large,
return it modulo 109 + 7.

Note that a prime number is a natural number greater than 1
that is not a product of two smaller natural numbers.
The prime factors of a number n is a list of prime numbers such that their product equals n.

Example 1:
Input: primeFactors = 5
Output: 6
Explanation: 200 is a valid value of n.
It has 5 prime factors: [2,2,2,5,5], and it has 6 nice divisors: [10,20,40,50,100,200].
There is not other value of n that has at most 5 prime factors and more nice divisors.
Example 2:
Input: primeFactors = 8
Output: 18

Constraints:
1 <= primeFactors <= 109
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
/*
The total number of good divisors will be the product of the amount of each type of prime factor.
In order to maximize this product, each prime number's frequency must not exceed 3.
If input is divisible by 3, answer is simply pow(3,primeFactors/3);
If primeFactors gives remainder 1, then maximization will require us to having 2 prime numbers in frequency two each, as 2 * 2> 3 * 1
If primeFactors gives remainder 2, then one prime number will have to have a frequency equal to two.
In order to preven TLE, we write an optimised power function, optimised using binary search.
*/
class Solution {
private:
    int mod = 1000000007;

    int power(long long base, int pow) {
        if (pow == 0)
            return 1;
        return (pow & 1 ? (base * power(base, pow - 1)) % mod : power((base * base) % mod, pow / 2)) % mod;
    }

public:
    int maxNiceDivisors(int primeFactors) {
        long ans = 1;
        if (primeFactors % 3 == 1 && primeFactors > 1) {
            ans = 4;
            primeFactors -= 4;
        } else if (primeFactors % 3 == 2) {
            ans = 2;
            primeFactors -= 2;
        }
        return (power(3, primeFactors / 3) * ans) % mod;
    }
};