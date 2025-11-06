/*
1399. Count Largest Group
https://leetcode.com/problems/count-largest-group/

Given an integer n.
Each number from 1 to n is grouped according to the sum of its digits.

Return how many groups have the largest size.

Example 1:
Input: n = 13
Output: 4
Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
[1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9]. There are 4 groups with largest size.

Example 2:
Input: n = 2
Output: 2
Explanation: There are 2 groups [1], [2] of size 1.

Example 3:
Input: n = 15
Output: 6

Example 4:
Input: n = 24
Output: 5

Constraints:
1 <= n <= 10^4
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
private:
    int getDigitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

public:
    int countLargestGroup(int n) {
        unordered_map<int, int> count;
        for (int i = 1; i <= n; ++i) {
            int sum = getDigitSum(i);
            count[sum] += 1;
        }

        int result = 0;
        int curMax = INT_MIN;
        for (auto& it : count) {
            if (it.second > curMax) {
                curMax = it.second;
                result = 1;
            } else if (it.second == curMax) {
                result += 1;
            }
        }
        return result;
    }
};