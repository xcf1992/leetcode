/*
342. Power of Four
Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

Example 1:

Input: 16
Output: true
Example 2:

Input: 5
Output: false
Follow up: Could you solve it without loops/recursion?
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
    bool isPowerOfFour(int num) {
        if (num <= 0) {
            return false;
        }

        if ((num & (num - 1)) != 0) {
            return false;
        }

        while (num != 0) {
            if (num == 1) {
                return true;
            }
            num >>= 2;
        }
        return false;
    }
};
