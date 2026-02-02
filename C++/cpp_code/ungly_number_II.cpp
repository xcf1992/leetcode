/*
https://leetcode.com/problems/ugly-number-ii/description/
264. Ugly Number II

An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.

Given an integer n, return the nth ugly number.



Example 1:

Input: n = 10
Output: 12
Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.
Example 2:

Input: n = 1
Output: 1
Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.


Constraints:

1 <= n <= 1690
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
#include <map>
using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> numbers;
        numbers.push_back(1);
        int multiply2 = 0;
        int multiply3 = 0;
        int multiply5 = 0;
        while (numbers.size() < n) {
            int nextNum = min(numbers[multiply2] * 2, min(numbers[multiply3] * 3, numbers[multiply5] * 5));
            numbers.push_back(nextNum);
            while (numbers[multiply2] * 2 <= nextNum) {
                multiply2++;
            }
            while (numbers[multiply3] * 3 <= nextNum) {
                multiply3++;
            }
            while (numbers[multiply5] * 5 <= nextNum) {
                multiply5++;
            }
        }
        return numbers.back();
    }
};