/*
 878. Nth Magical Number
 A positive integer is magical if it is divisible by either A or B.

 Return the N-th magical number.  Since the answer may be very large, return it modulo 10^9 + 7.

 Example 1:

 Input: N = 1, A = 2, B = 3
 Output: 2
 Example 2:

 Input: N = 4, A = 2, B = 3
 Output: 6
 Example 3:

 Input: N = 5, A = 2, B = 4
 Output: 10
 Example 4:

 Input: N = 3, A = 6, B = 4
 Output: 8


 Note:

 1 <= N <= 10^9
 2 <= A <= 40000
 2 <= B <= 40000
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
 4 points to figure out:

 Get gcd (greatest common divisor) and lcm (least common multiple) of (A, B).
 (a, b) = (A, B) while b > 0: (a, b) = (b, a % b)
 then, gcd = a and lcm = A * B / a

 How many magic numbers <= x ?
 By inclusion exclusion principle, we have:
 x / A + x / B - x / lcm

 Set our binary search range
 Lower bound is min(A, B), I just set left = 2.
 Upper bound is N * min(A, B), I just set right = 10 ^ 14.

 binary search, find the smallest x that x / A + x / B - x / lcm = N
 */
class Solution {
private:
    int mod = 1e9 + 7;

    int gcd(int a, int b) {
        if (a < b) {
            return gcd(b, a);
        }
        return b > 0 ? gcd(b, a % b) : a;
    }

    int lcm(int a, int b) {
        return a * b / gcd(a, b);
    }
public:
    int nthMagicalNumber(int N, int A, int B) {
        long left = 2;
        long right = 1e14;
        while (left < right) {
            long mid = left + (right - left) / 2;
            if (mid / A + mid / B - mid / lcm(A, B) < N) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        return left % mod;
    }
};
