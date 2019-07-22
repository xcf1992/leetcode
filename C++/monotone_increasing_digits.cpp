/*
738. Monotone Increasing Digits
Given a non-negative integer N,
find the largest number that is less than or equal to N with monotone increasing digits.
(Recall that an integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.)

Example 1:
Input: N = 10
Output: 9

Example 2:
Input: N = 1234
Output: 1234

Example 3:
Input: N = 332
Output: 299
Note: N is an integer in the range [0, 10^9].
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
Intuition

One initial thought that comes to mind is we can always have a candidate answer of d999...9
(a digit 0 <= d <= 9 followed by some number of nines.)
For example if N = 432543654, we could always have an answer of at least 399999999.

We can do better. For example, when the number is 123454321,
we could have a candidate of 123449999.
It seems like a decent strategy is to take a monotone increasing prefix of N,
then decrease the number before the "cliff" (the index where adjacent digits decrease for the first time)
if it exists, and replace the rest of the characters with 9s.

When does that strategy fail? If N = 333222, then our strategy would give us the candidate answer of 332999 -
but this isn't monotone increasing.
However, since we are looking at all indexes before the original first occurrence of a cliff,
the only place where a cliff could exist, is next to where we just decremented a digit.

Thus, we can repair our strategy, by successfully morphing our answer 332999 -> 329999 -> 299999 with a linear scan.

Algorithm

We'll find the first cliff S[i-1] > S[i].
Then, while the cliff exists, we'll decrement the appropriate digit and move i back.
Finally, we'll make the rest of the digits 9s and return our work.

We can prove our algorithm is correct because every time we encounter a cliff,
the digit we decrement has to decrease by at least 1.
Then, the largest possible selection for the rest of the digits is all nines,
which is always going to be monotone increasing with respect to the other digits occurring earlier in the number.
*/
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string num = to_string(N);
        int len = num.size();
        int pos = 1;
        while (pos < len and num[pos - 1] <= num[pos]) {
            pos += 1;
        }
        while (pos > 0 and pos < len and num[pos - 1] > num[pos]) {
            num[pos - 1] -= 1;
            pos -= 1;
        }
        for (int i = pos + 1; i < len; ++i) {
            num[i] = '9';
        }
        return stoi(num);
    }
};

class Solution1 {
public:
    int monotoneIncreasingDigits(int N) {
        string num = to_string(N);
        int i = 0;
        while (i < num.size() - 1) {
            if (num[i] > num[i + 1]) {
                break;
            }
            i++;
        }

        if (i == num.size() - 1) {
            return N;
        }

        while (i >= 1 && num[i - 1] == num[i]) {
            i--;
        }

        num[i] -= 1;
        do {
            i += 1;
            num[i] = '9';
        } while (i < num.size());

        int result = 0;
        for (char c : num) {
            result = result * 10 + c - '0';
        }
        return result;
    }
};
