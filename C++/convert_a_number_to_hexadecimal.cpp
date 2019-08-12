/*
405. Convert a Number to Hexadecimal
Given an integer,
write an algorithm to convert it to hexadecimal.
For negative integer, two’s complement method is used.

Note:

All letters in hexadecimal (a-f) must be in lowercase.
The hexadecimal string must not contain extra leading 0s.
If the number is zero, it is represented by a single zero character '0';
otherwise, the first character in the hexadecimal string will not be the zero character.
The given number is guaranteed to fit within the range of a 32-bit signed integer.
You must not use any method provided by the library which converts/formats the number to hex directly.

Example 1:

Input:
26

Output:
"1a"
Example 2:

Input:
-1

Output:
"ffffffff"
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

class Solution {
private:
    const string HEX = "0123456789abcdef";
public:
    string toHex(int num) {
        if (num == 0) {
            return "0";
        }

        string result = "";
        int count = 0;
        while (num != 0 and count < 8) { // use != 0, in order to transform negative number
            result.push_back(HEX[num & 0xf]);
            num >>= 4;
            count++;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
