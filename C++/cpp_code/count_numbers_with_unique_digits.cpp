/*
357. Count Numbers with Unique Digits
https://leetcode.com/problems/count-numbers-with-unique-digits/

Given a non-negative integer n,
count all numbers with unique digits, x,
where 0 ≤ x < 10^n

Example:
Input: 2
Output: 91
Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100,
             excluding 11,22,33,44,55,66,77,88,99
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
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) {
            return 1;
        }

        int result = 10;
        int multiplier = 9;
        for (int i = 1; i < n; i++) {
            multiplier *= (10 - i);
            result += multiplier;
        }
        return result;
    }
};

class Solution1 {
public:
    int countNumbersWithUniqueDigits(int n) {
        vector<int> result(n + 1, 0);
        result[0] = 1;
        int multiplier = 9;
        for (int i = 1; i <= n; i++) {
            result[i] = result[i - 1] + multiplier;
            if (i <= 9) {
                multiplier *= (10 - i);
            }
            else {
                multiplier = 0;
            }
        }
        return result[n];
    }
};
