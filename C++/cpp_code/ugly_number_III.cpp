/*
1201. Ugly Number III
https://leetcode.com/problems/ugly-number-iii/

Write a program to find the n-th ugly number.
Ugly numbers are positive integers which are divisible by a or b or c.

Example 1:
Input: n = 3, a = 2, b = 3, c = 5
Output: 4
Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.

Example 2:
Input: n = 4, a = 2, b = 3, c = 4
Output: 6
Explanation: The ugly numbers are 2, 3, 4, 6, 8, 9, 12... The 4th is 6.

Example 3:
Input: n = 5, a = 2, b = 11, c = 13
Output: 10
Explanation: The ugly numbers are 2, 4, 6, 8, 10, 11, 12, 13... The 5th is 10.

Example 4:
Input: n = 1000000000, a = 2, b = 217983653, c = 336916467
Output: 1999999984

Constraints:
1 <= n, a, b, c <= 10^9
1 <= a * b * c <= 10^18
It's guaranteed that the result will be in range [1, 2 * 10^9]
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
#include <numeric>
using namespace std;
/*
但是容斥只能找到一个数字 N 之内有多少个丑数。
想找到第n 个丑数，就需要进行二分了。
*/
class Solution {
private:
    long long ab;
    long long ac;
    long long bc;
    long long abc;

    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    long long lcm(long long a, long long b) {
        return a * b / (gcd(a, b));
    }

    int getCount(long long n, long long a, long long b, long long c) {
        return n / a + n / b + n / c - n / ab - n / ac - n / bc + n / abc;
    }

public:
    int nthUglyNumber(int n, int a, int b, int c) {
        ab = lcm(a, b);
        ac = lcm(a, c);
        bc = lcm(b, c);
        abc = lcm(ab, c);

        int left = 1;
        int right = 1 + 2 * 1e9 + 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            int count = getCount(mid, a, b, c);
            if (count < n) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};

class Solution1 {
    // TLE
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        int num = 1;
        int countA = 1;
        int countB = 1;
        int countC = 1;
        while (n >= 0) {
            num = min(countA * a, min(countB * b, countC * c));
            if (num == countA * a) {
                countA += 1;
            }
            if (num == countB * b) {
                countB += 1;
            }
            if (num == countC * c) {
                countC += 1;
            }
            n -= 1;
        }
        return num;
    }
};