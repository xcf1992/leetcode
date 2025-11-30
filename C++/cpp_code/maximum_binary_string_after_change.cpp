/*
1702. Maximum Binary String After Change
https://leetcode.com/problems/maximum-binary-string-after-change/

You are given a binary string binary consisting of only 0's or 1's.
You can apply each of the following operations any number of times:

Operation 1: If the number contains the substring "00", you can replace it with "10".
For example, "00010" -> "10010"
Operation 2: If the number contains the substring "10", you can replace it with "01".
For example, "00010" -> "00001"
Return the maximum binary string you can obtain after any number of operations.
Binary string x is greater than binary string y
if x's decimal representation is greater than y's decimal representation.

Example 1:
Input: binary = "000110"
Output: "111011"
Explanation: A valid transformation sequence can be:
"000110" -> "000101"
"000101" -> "100101"
"100101" -> "110101"
"110101" -> "110011"
"110011" -> "111011"
Example 2:
Input: binary = "01"
Output: "01"
Explanation: "01" cannot be transformed any further.

Constraints:
1 <= binary.length <= 105
binary consist of '0' and '1'.
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
#include <climits>
#include <set>
#include <numeric>
using namespace std;
/*
We don't need touch the starting 1s, they are already good.

For the rest part,
we continuely take operation 2,
making the string like 00...00011...11

Then we continuely take operation 1,
making the string like 11...11011...11.

Complexity
Time O(n)
Space O(n)
*/
class Solution {
public:
    string maximumBinaryString(string s) {
        int ones = 0, zeros = 0, n = s.length();
        for (auto& c : s) {
            if (c == '0')
                zeros++;
            else if (zeros == 0)
                ones++;
            c = '1';
        }
        if (ones < n)
            s[ones + zeros - 1] = '0';
        return s;
    }
};