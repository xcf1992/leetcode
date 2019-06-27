/*
 1015. Numbers With 1 Repeated Digit

 Given a positive integer N, return the number of positive integers less than or equal to N that have at least 1 repeated digit.

 Example 1:

 Input: 20
 Output: 1
 Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
 Example 2:

 Input: 100
 Output: 10
 Explanation: The positive numbers (<= 100) with atleast 1 repeated digit are 11, 22, 33, 44, 55, 66, 77, 88, 99, and 100.
 Example 3:

 Input: 1000
 Output: 262


 Note:

 1 <= N <= 10^9
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
#include <set>
#include <numeric>
using namespace std;

/*
 Count res the Number Without Repeated Digit
 Then the number with repeated digits = N - res

 Similar as
 788. Rotated Digits
 902. Numbers At Most N Given Digit Set

 Explanation:
 Transform N + 1 to arrayList
 Count the number with digits < n
 Count the number with same prefix
 For example,
 if N = 8765, L = [8,7,6,6],
 the number without repeated digit can the the following format:
 XXX
 XX
 X
 1XXX ~ 7XXX
 80XX ~ 86XX
 870X ~ 875X
 8760 ~ 8765

 Time Complexity:
 the number of permutations A(m,n) is O(1)
 We count digit by digit, so it's O(logN)

 Consider the given number is 5234. Then N+1 = 5235.

 It is a 4-digit number, and hence all the 1-digit, 2-digit and 3-digit number permutations are definitely less than 5235.

 Now let us see the 4-digit permutations. As per the logic being followed,
 we are counting number of permutations for a given number of digits.

 So we cannot separately count 'numbers less than given number' following this permutation formula without 'prefixing' it digit-by-digit of the given number.
 For example:
 4 digit permutations look like this:
 1XXX to 4XXX (4 digit nos. less than 5XXX. If we add in 5XXX as well,
 then we will incorrectly count, for instance, 5567 which is greater than 5235)

 50XX to 51XX (prefix '5' at the start and 2nd digit should be less than 2.
 If '2' is also counted, we will incorrectly count, for instance, 5240 which is greater than 5235)

 520X to 522X (prefix '52' at the start and 3rd digit should be less than 3.
 If '3' is also counted, we will incorrectly count, for instance, 5235 which is greater than 5235)

 5230 to 5234 (prefix '523' at the start and 4th digit should be less than 5.
 If '5' is also counted, we will incorrectly count,
 for instance, 5235 which is equal to 5235 but we need only numbers < 5235 and not == 5235)

 If we won't consider the 'prefix', we will calculate all the possible permutations for a 4-digit number,
 which includes numbers greater than 5235 as well. Hence to avoid counting such numbers,
 we are following the prefix logic. We 'fix' the initial digits and permute the next ones. Hope this clarifies your confusion :)
 */
class Solution {
private:
    int permutation(int m, int n) {
        return n == 0 ? 1 : permutation(m, n - 1) * (m - n + 1);
    }
public:
    int numDupDigitsAtMostN(int N) {
        vector<int> digit;
        for (int i = N + 1; i > 0; i /= 10) {
            digit.push_back(i % 10);
        }
        reverse(digit.begin(), digit.end());

        int result = 0;
        int n = digit.size();
        for (int i = 1; i < n; i++) {
            result += 9 * permutation(9, i - 1);
        }

        // Count the number with same prefix
        unordered_set<int> seen;
        for (int i = 0; i < n; i++) {
            for (int j = i > 0 ? 0 : 1; j < digit[i]; j++) {
                if (seen.find(j) == seen.end()) {
                    result += permutation(9 - i, n - i - 1);
                }
            }
            if (seen.find(digit[i]) != seen.end()) {
                break;
            }
            seen.insert(digit[i]);
        }
        return N - result;
    }
};
