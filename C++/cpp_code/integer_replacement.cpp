/*
397. Integer Replacement
https://leetcode.com/problems/integer-replacement/

Given a positive integer n and you can do operations as follow:
If n is even, replace n with n/2.
If n is odd, you can replace n with either n + 1 or n - 1.
What is the minimum number of replacements needed for n to become 1?

Example 1:
Input:
8
Output:
3
Explanation:
8 -> 4 -> 2 -> 1

Example 2:
Input:
7
Output:
4
Explanation:
7 -> 8 -> 4 -> 2 -> 1
or
7 -> 6 -> 3 -> 2 -> 1
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
using namespace std;
/*
possible dp solution
no need to use int dp[n + 1], you just need int dp[(n + 1)/2] or less.

my dynamic programming:

dp(n) = dp(n/2)+1 n is even

dp(n) = min(dp(n-1), dp(n+1)) +1 n is odd, we can not resolve dp(n+1). so :
dp(n) = min(dp(n-1), dp((n+1)/2)+1)+1 n is odd, now we just need to resolve dp((n+1)/2).
*/
class Solution {
private:
    unordered_map<int, int> cache;

public:
    int integerReplacement(int n) {
        if (cache.find(n) != cache.end()) {
            return cache[n];
        }

        if (n <= 3) {
            return n - 1;
        }

        if (n % 2 == 0) {
            cache[n] = 1 + integerReplacement(n / 2);
        } else {
            cache[n] = 1 + min(integerReplacement(n - 1), 1 + integerReplacement(((long)n + 1) / 2));
        }
        return cache[n];
    }
};

class Solution1 {
public:
    int integerReplacement(int n) {
        int result = 0;
        unsigned num = n;
        while (num > 3) {
            if (num % 2 == 0) {
                num >>= 1;
            } else if (num & 2) {
                // 0x11
                num += 1;
            } else {
                // 0x01
                num -= 1;
            }
            result += 1;
        }
        return result + num - 1;
    }
};