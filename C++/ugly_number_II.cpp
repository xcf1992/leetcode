/*
264. Ugly Number II

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.

Example:

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note:

1 is typically treated as an ugly number.
n does not exceed 1690.
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
We have an array k of first n ugly number.
We only know, at the beginning, the first one, which is 1.

Then k[1] = min( k[0]x2, k[0]x3, k[0]x5).
The answer is k[0]x2.
So we move 2's pointer to 1.

Then we test:
k[2] = min( k[1]x2, k[0]x3, k[0]x5). And so on.
Be careful about the cases such as 6, in which we need to forward both pointers of 2 and 3.

x here is multiplication.
*/
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
            if (numbers[multiply2] * 2 == nextNum) {
                multiply2++;
            }
            if (numbers[multiply3] * 3 == nextNum) {
                multiply3++;
            }
            if (numbers[multiply5] * 5 == nextNum) {
                multiply5++;
            }
        }
        return numbers.back();
    }
};
