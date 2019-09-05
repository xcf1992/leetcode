/*
Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:

Input: 121
Output: true
Example 2:

Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Follow up:

Coud you solve it without converting the integer to a string?
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
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        if (x < 10) {
            return true;
        }

        vector<int> digits;
        while (x != 0) {
            digits.push_back(x % 10);
            x /= 10;
        }

        int start = 0;
        int end = digits.size() - 1;
        while (start < end) {
            if (digits[start] != digits[end]) {
                return false;
            }
            start += 1;
            end -= 1;
        }
        return true;
    }
};

class Solution {
public:
    bool isPalindrome(int x) {
        if ( x < 0) {
            return false;
        }

        int hehe = 1;
        int times = 1;
        int y = x;
        while ( y / 10 != 0) {
            y = y / 10;
            hehe *= 10;
            times += 1;
        }

        int temp = x;
        while ( times != 0 and times != 1) {
            int a = x % 10;
            int b = temp / hehe;

            if ( a != b) {
                return false;
            }
            else {
                x = x / 10;
                temp = temp % hehe;
                hehe = hehe / 10;
            }

            times -= 2;
        }

        return true;
    }
};