/*
326. Power of Three
Given an integer, write a function to determine if it is a power of three.

Example 1:

Input: 27
Output: true
Example 2:

Input: 0
Output: false
Example 3:

Input: 9
Output: true
Example 4:

Input: 45
Output: false
Follow up:
Could you do it without using any loop / recursion?
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
public:
    bool isPowerOfThree(int n) {
        return (n == 0x1)
        or
                (n == 0x3)
        or
                (n == 0x9)
        or
                (n == 0x1b)
        or
                (n == 0x51)
        or
                (n == 0xf3)
        or
                (n == 0x2d9)
        or
                (n == 0x88b)
        or
                (n == 0x19a1)
        or
                (n == 0x4ce3)
        or
                (n == 0xe6a9)
        or
                (n == 0x2b3fb)
        or
                (n == 0x81bf1)
        or
                (n == 0x1853d3)
        or
                (n == 0x48fb79)
        or
                (n == 0xdaf26b)
        or
                (n == 0x290d741)
        or
                (n == 0x7b285c3)
        or
                (n == 0x17179149)
        or
                (n == 0x4546b3db);
    }
};