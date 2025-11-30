/*
1017. Convert to Base -2
https://leetcode.com/problems/convert-to-base-2/

Given a number N, return a string consisting of "0"s and "1"s that represents its value in base -2 (negative two).
The returned string must have no leading zeroes, unless the string is "0".

Example 1:
Input: 2
Output: "110"
Explantion: (-2) ^ 2 + (-2) ^ 1 = 2

Example 2:
Input: 3
Output: "111"
Explantion: (-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3

Example 3:
Input: 4
Output: "100"
Explantion: (-2) ^ 2 = 4

Note:
0 <= N <= 10^9
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
#include <set>
#include <numeric>
using namespace std;
/*
Intuition:
Maybe write a base2 function first?
How about add minus -?
Done.

Explanation:
base2 function is quite basis of basis.
check last digit, shift to right.
base-2 is totally no difference, just add a sign -.


Time Complexity:
O(logN) Time, O(logN) space.
Note that I didn't deal with string concatenation,
and just take this part as O(1).

Instead of create a new string each time,
we can improve this process using some operations join/reverse or data structure list/vector .
Like Java we may need StringBuilder,
but those are not what I want to discuss deeply here.
*/
class Solution {
public:
    string baseNeg2(int N) {
        if (N == 0) {
            return "0";
        }

        string result = "";
        while (N != 0) {
            result.push_back((N & 1) + '0');
            N = 0 - (N >> 1);
        }
        reverse(result.begin(), result.end());
        return result;
    }
};