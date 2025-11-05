/*
906. Super Palindromes

Let's say a positive integer is a superpalindrome if it is a palindrome,
and it is also the square of a palindrome.

Now, given two positive integers L and R (represented as strings),
return the number of superpalindromes in the inclusive range [L, R].

Example 1:
Input: L = "4", R = "1000"
Output: 4
Explanation: 4, 9, 121, and 484 are superpalindromes.
Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a palindrome.

Note:
1 <= len(L) <= 18
1 <= len(R) <= 18
L and R are strings representing integers in the range [1, 10^18).
int(L) <= int(R)
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
Intuition

Say P = R^2 is a superpalindrome.

Because R is a palindrome, the first half of the digits in R determine R up to two possibilities.
We can iterate through these digits:
let k be the first half of the digits in R.
For example, if k = 1234, then R = 1234321 or R = 12344321.
Each possibility has either an odd or an even number of digits in R.
because P < 10 ^ 18, so R < 10^9, R = kork'(concatenation),
where k and k' reversed(and also possibly truncated by one digit)
and k < 10^5 = MAGIC

Algorithm

For each 1 <= k < MAGIC,
let's create the associated palindrome R,
and check whether R^2 is a palindrome.

We should handle the odd and even possibilities separately,
as we would like to break early so as not to do extra work.

To check whether an integer is a palindrome,
we could check whether it is equal to its reverse.
To create the reverse of an integer, we can do it digit by digit.
*/
class Solution {
private:
    int MAGIC = 1e5;

    long long reverseNum(long long num) {
        long long result = 0;
        while (num > 0) {
            result = result * 10 + num % 10;
            num /= 10;
        }
        return result;
    }

    bool isPalindrome(long long num) {
        return num == reverseNum(num);
    }

public:
    int superpalindromesInRange(string L, string R) {
        long left = stol(L);
        long right = stol(R);
        int result = 0;
        for (int i = 1; i < MAGIC; i++) {
            string numStr = to_string(i);
            string reverseNum = numStr;
            reverse(reverseNum.begin(), reverseNum.end());

            string numStr2 = numStr + reverseNum;
            numStr += reverseNum.substr(1);
            unsigned long long num1 = stoll(numStr);
            unsigned long long num2 = stoll(numStr2);

            num1 *= num1;
            num2 *= num2;
            if (num1 >= left and num1
            <=
            right and isPalindrome(num1)
            )
            {
                result += 1;
            }
            if (num2 >= left and num2
            <=
            right and isPalindrome(num2)
            )
            {
                result += 1;
            }
            if (num1 > right and num2
            >
            right
            )
            {
                break;
            }
        }
        return result;
    }
};