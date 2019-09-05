/*
788. Rotated Digits
X is a good number if after rotating each digit individually by 180 degrees,
we get a valid number that is different from X.
Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation.
0, 1, and 8 rotate to themselves;
2 and 5 rotate to each other;
6 and 9 rotate to each other,
and the rest of the numbers do not rotate to any other number and become invalid.

Now given a positive number N, how many numbers X from 1 to N are good?

Example:
Input: 10
Output: 4
Explanation:
There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
Note:

N  will be in range [1, 10000].
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
Using a int[] for dp.
dp[i] = 0, invalid number
dp[i] = 1, valid and same number
dp[i] = 2, valid and different number
*/
class Solution {
public:
    int rotatedDigits(int N) {
        vector<int> dp(N + 1, 0);
        int result = 0;
        for (int i = 0; i <= N; ++i) {
            if (i == 0 or i == 1 or i == 8) {
                dp[i] = 1; // rotated same
            }
            else if (i == 2 or i == 5 or i == 6 or i == 9) { // rotated differently
                dp[i] = 2;
                result += 1;
            }
            else if (i >= 10) {
                int left = dp[i / 10];
                int right = dp[i % 10];
                if (left == 1 and right == 1) {
                    dp[i] = 1;
                }
                else if (left >= 1 and right >= 1) {
                    dp[i] = 2;
                    result += 1;
                }
            }
        }
        return result;
    }
};

/*
 * http://www.frankmadrid.com/ALudicFallacy/2018/02/28/rotated-digits-leet-code-788/
 * The following four arrays were defined to avoid long compound boolean expressions:
 * 'if(digit == 2 or digit == 5 or digit == 6 or digit == 9) { ... }'
 * which instead keeps track of such information cumulatively. For example,
 * differentRotation[7] = 3 means 3 numbers in the range of [0,7] are new numbers, namely,
 * the new numbers post-rotation 2,5, and 6.
*/
class Solution {
private:
    int type[10]               = {0,0,1,2,2,1,1,2,0,1};  // 'Same' 'New' or 'Invalid' numbers
    int differentRotations[10] = {0,0,1,1,1,2,3,3,3,4};  // Cumulative: New number
    int validRotations[10]     = {1,2,3,3,3,4,5,5,6,7};  // Cumulative: Valid number
    int sameRotations[10]      = {1,2,2,2,2,2,2,2,3,3};  // Cumulative: Same number

    // Counts the good numbers in the range of [000..0, X00..0] where str[0] = X. Implements
    // dynamic programming to indicate if a new number has been seen.
    int countRotations(string str, bool isNewNumber) {
        int digit = str[0] - '0';  // Converts char to int (see ASCII Table mathematics)
        if (str.length() == 1) {
            return isNewNumber ? validRotations[digit] : differentRotations[digit];
        }

        int ret = 0;
        if (digit != 0) {
            // Get all valid numbers (Idea #1)
            ret += validRotations[digit - 1] * pow(7, str.length() - 1);

            // If a new number has not been seen, subtract all non-good number paths (Idea #2)
            if(!isNewNumber) {
                ret -= sameRotations[digit-1] * pow(3, str.length() - 1);
            }
        }

        if (type[digit] == 1) {
            isNewNumber = true;
        }

          // If the digit is valid, then recursively call function on remaining n-1 numbers
        if (type[digit] != 2) {
            ret += countRotations(str.substr(1), isNewNumber);
        }
        return ret;
    }
public:

    // Converts N into a string where the most significant bit is at index 0
    int rotatedDigits(int N) {
        return countRotations(to_string(N), false);
    }
};


/*
 X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X. A number is valid if each digit remains a digit after rotation. 0, 1, and 8 rotate to themselves; 2 and 5 rotate to each other; 6 and 9 rotate to each other, and the rest of the numbers do not rotate to any other number.

 Now given a positive number N, how many numbers X from 1 to N are good?

 Example:
 Input: 10
 Output: 4
 Explanation:
 There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
 Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
*/

class Solution1 {
public:
    int rotatedDigits(int N) {
        vector<int> goodSame({1,2,2,2,2,2,2,2,3,3});
        vector<int> goodDiff({0,0,1,1,1,2,3,3,3,4});
        vector<int> digitType({0,0,1,2,2,1,1,2,0,1});

        if (N < 10) {
            return goodDiff[N];
        }
        string num = to_string(N);
        int result = 0;
        int length = num.size();
        int digit = num[0] - '0';
        result += (goodSame[digit - 1] + goodDiff[digit - 1]) * pow(7, length - 1) - goodSame[digit - 1] * pow(3, length - 1);
        bool allSame = true;

        if (digitType[digit] == 2) {
            return result;
        }

        if (digitType[digit] == 1) {
            allSame = false;
        }
        for (int i = length - 2; i >= 0; i--) {
            digit = num[length - i - 1] - '0';
            result += (goodSame[digit - 1] + goodDiff[digit - 1]) * pow(7, i);

            if (allSame) {
                result -= (goodSame[digit - 1]) * pow(3, i);
            }

            if (digitType[digit] == 2) {
                return result;
            }

            if (digitType[digit] == 1) {
                if (i == 0) {
                    result += 1;
                }
                allSame = false;
            }
            else if (i == 0) {
                if (!allSame) {
                    result += 1;
                }
            }
        }
        return result;
    }
};
