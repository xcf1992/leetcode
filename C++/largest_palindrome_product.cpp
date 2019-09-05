/*
 479. Largest Palindrome Product
 Find the largest palindrome made from the product of two n-digit numbers.
 Since the result could be very large, you should return the largest palindrome mod 1337.

 Example:
 Input: 2
 Output: 987
 Explanation: 99 x 91 = 9009, 9009 % 1337 = 987

 Note:
 The range of n is [1,8].
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
/*
Bascially,
it goes through all palindrome numbers with 2n digits in a descending order.
For each palindrome number u, it checks if the number can be divided by a number x with n digits.
If so, u % x should also be a number which has n digits.
As it's in descending order, the first number that meets this check is the largest palindrome number we want.

There are no two numbers of equal number of digits that would produce 999.

To your point, it may be possible to find a palindrome that is smaller than (n x 2) digits by multiplying two n-digit numbers.
But, it will certainly not be the largest and therefore can be ignored. Try it out yourself.
*/
class Solution {
private:
    long buildPalindrome(int value) {
        string s = to_string(value);
        reverse(s.begin(), s.end());
        return stol(to_string(value) + s);
    }
public:
    int largestPalindrome(int n) {
        if (n == 1) {
            return 9;
        }

        int upper = pow(10, n) - 1;
        int lower = pow(10, n - 1);
        for (int v = upper; v >= lower; --v) {
            long palindrome = buildPalindrome(v);
            for (long factor = upper; factor * factor >= palindrome; --factor) {
                if (palindrome % factor == 0 and palindrome / factor <= upper) {
                    return palindrome % 1337;
                }
            }
        }
        return 0;
    }
};
