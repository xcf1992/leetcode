/*
https://leetcode.com/problems/hamming-distance/description/
461. Hamming Distance

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, return the Hamming distance between them.



Example 1:

Input: x = 1, y = 4
Output: 2
Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
The above arrows point to positions where the corresponding bits are different.
Example 2:

Input: x = 3, y = 1
Output: 1


Constraints:

0 <= x, y <= 231 - 1


Note: This question is the same as 2220: Minimum Bit Flips to Convert Number.
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
using namespace std;

class Solution {
public:
    int hammingDistance(int x, int y) {
        int xorValue = x ^ y;
        int distance = 0;
        while (xorValue != 0) {
            if (xorValue & 1 != 0) {
                distance++;
            }
            xorValue >>= 1;
        }
        return distance;
    }
};