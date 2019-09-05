/*
367. Valid Perfect Square
Given a positive integer num, write a function which returns True if num is a perfect square else False.

Note: Do not use any built-in library function such as sqrt.

Example 1:

Input: 16
Output: true
Example 2:

Input: 14
Output: false
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
    bool isPerfectSquare(int num) {
        int left = 0;
        int right = num;
        while (left <= right) {
            long mid = left + (right - left) / 2;
            if (mid * mid == (long) num) {
                return true;
            }

            if (mid * mid > num) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return false;
    }
};

class Solution1 {
public:
    bool isPerfectSquare(int num) {
        int diff = 1;
        int cur = 0;
        while (cur <= num and cur >= 0) {
            if (cur == num) {
                return true;
            }

            cur += diff;
            diff += 2;
        }

        return false;
    }
};

int main() {
    Solution s;
    return 0;
}