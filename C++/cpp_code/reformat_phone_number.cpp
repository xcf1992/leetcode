/*
1694. Reformat Phone Number
https://leetcode.com/problems/reformat-phone-number/

You are given a phone number as a string number.
number consists of digits, spaces ' ', and/or dashes '-'.

You would like to reformat the phone number in a certain manner.
Firstly, remove all spaces and dashes.
Then, group the digits from left to right into blocks of length 3 until there are 4 or fewer digits.
The final digits are then grouped as follows:

2 digits: A single block of length 2.
3 digits: A single block of length 3.
4 digits: Two blocks of length 2 each.
The blocks are then joined by dashes.
Notice that the reformatting process should never produce any blocks of length 1
and produce at most two blocks of length 2.

Return the phone number after formatting.

Example 1:
Input: number = "1-23-45 6"
Output: "123-456"
Explanation: The digits are "123456".
Step 1: There are more than 4 digits, so group the next 3 digits. The 1st block is "123".
Step 2: There are 3 digits remaining, so put them in a single block of length 3. The 2nd block is "456".
Joining the blocks gives "123-456".

Example 2:
Input: number = "123 4-567"
Output: "123-45-67"
Explanation: The digits are "1234567".
Step 1: There are more than 4 digits, so group the next 3 digits. The 1st block is "123".
Step 2: There are 4 digits left, so split them into two blocks of length 2. The blocks are "45" and "67".
Joining the blocks gives "123-45-67".

Example 3:
Input: number = "123 4-5678"
Output: "123-456-78"
Explanation: The digits are "12345678".
Step 1: The 1st block is "123".
Step 2: The 2nd block is "456".
Step 3: There are 2 digits left, so put them in a single block of length 2. The 3rd block is "78".
Joining the blocks gives "123-456-78".

Example 4:
Input: number = "12"
Output: "12"

Example 5:
Input: number = "--17-5 229 35-39475 "
Output: "175-229-353-94-75"

Constraints:
2 <= number.length <= 100
number consists of digits and the characters '-' and ' '.
There are at least two digits in number.
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
Assume max digit in n is x.
Because deci-binary only contains 0 and 1,
we need at least x numbers to sum up a digit x.

Now we contruct an answer,
Take n = 135 as an example,
we initilize 5 deci-binary number with lengh = 3,
a1 = 000
a2 = 000
a3 = 000
a4 = 000
a5 = 000

For the first digit, we fill the first n[0] number with 1
For the second digit, we fill the first n[1] number with 1
For the third digit, we fill the first n[2] number with 1

So we have
a1 = 111
a2 = 011
a3 = 011
a4 = 001
a5 = 001

Finally, we have 111+11+11+1+1=135.


Complexity
Time O(L)
Space O(1)
*/
class Solution {
public:
    string reformatNumber(string number) {
        string purified = "";
        for (char c: number) {
            if (isdigit(c)) {
                purified.push_back(c);
            }
        }

        string result = "";
        int len = purified.size();
        int left = len % 3;
        for (int i = 0; i < len / 3; ++i) {
            result += purified.substr(i * 3, 3);
            result.push_back('-');
        }
        if (left == 0 or left
        ==
        1
        )
        {
            result.pop_back();
        }
        if (left == 2) {
            result += purified.substr(len - 2, 2);
        }
        if (left == 1) {
            result.pop_back();
            result.push_back('-');
            result += purified.substr(len - 2, 2);
        }
        return result;
    }
};