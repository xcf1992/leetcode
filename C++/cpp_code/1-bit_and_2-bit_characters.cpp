/*
717. 1-bit and 2-bit Characters
We have two special characters.
The first character can be represented by one bit 0.
The second character can be represented by two bits (10 or 11).

Now given a string represented by several bits.
Return whether the last character must be a one-bit character or not.
The given string will always end with a zero.

Example 1:
Input:
bits = [1, 0, 0]
Output: True
Explanation:
The only way to decode it is two-bit character and one-bit character. So the last character is one-bit character.
Example 2:
Input:
bits = [1, 1, 1, 0]
Output: False
Explanation:
The only way to decode it is two-bit character and two-bit character. So the last character is NOT one-bit character.
Note:

1 <= len(bits) <= 1000.
bits[i] is always 0 or 1.
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
When reading from the i-th position,
if bits[i] == 0,
the next character must have 1 bit;
else if bits[i] == 1,
the next character must have 2 bits.

We increment our read-pointer i to the start of the next character appropriately.
At the end, if our pointer is at bits.length - 1,
then the last character must have a size of 1 bit.
*/
class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int i = 0;
        int n = bits.size();
        while (i < n - 1) {
            i += bits[i] + 1;
        }
        return i == n - 1;
    }
};