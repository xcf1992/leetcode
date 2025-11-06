/*
670. Maximum Swap
https://leetcode.com/problems/maximum-swap/

Given a non-negative integer,
you could swap two digits at most once to get the maximum valued number.
Return the maximum valued number you could get.

Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.

Example 2:
Input: 9973
Output: 9973
Explanation: No swap.

Note:
The given number is in the range [0, 108]
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
#include <map>
using namespace std;

class Solution {
public:
    int maximumSwap(int num) {
        string number = to_string(num);
        int n = number.size();
        vector<pair<char, int>> bigger(n, {'0', -1});

        char curMax = number.back();
        int pos = n - 1;
        for (int i = number.size() - 2; i >= 0; --i) {
            if (number[i] > curMax) {
                curMax = number[i];
                pos = i;
            } else if (number[i] < curMax) {
                bigger[i] = {curMax, pos};
            }
        }

        for (int i = 0; i < n - 1; ++i) {
            if (bigger[i].first != '0') {
                swap(number[i], number[bigger[i].second]);
                break;
            }
        }
        return stoi(number);
    }
};

class Solution1 {
public:
    int maximumSwap(int num) {
        if (num < 10) {
            return num;
        }

        vector<int> digits;
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }

        int maxIndex = -1;
        int leftIndex = -1;
        int rightIndex = -1;
        for (int i = 0; i < digits.size(); i++) {
            if (maxIndex == -1 or digits[maxIndex] < digits[i]) {
                maxIndex = i;
            } else {
                leftIndex = maxIndex;
                rightIndex = i;
            }
        }

        swap(digits[leftIndex], digits[rightIndex]);
        int result = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            result = result * 10 + digits[i];
        }
        return result;
    }
};