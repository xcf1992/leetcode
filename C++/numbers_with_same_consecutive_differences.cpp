/*
967. Numbers With Same Consecutive Differences
https://leetcode.com/problems/numbers-with-same-consecutive-differences/

Return all non-negative integers of length N such that the absolute difference between every two consecutive digits is K.

Note that every number in the answer must not have leading zeros except for the number 0 itself.
For example, 01 has one leading zero and is invalid, but 0 is valid.

You may return the answer in any order.

Example 1:
Input: N = 3, K = 7
Output: [181,292,707,818,929]
Explanation: Note that 070 is not a valid number, because it has leading zeroes.

Example 2:
Input: N = 2, K = 1
Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]


Note:

1 <= N <= 9
0 <= K <= 9
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
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> numsSameConsecDiff(int N, int K) {
        vector<int> result;
        for (int i = 0; i < 10; i++) {
            result.push_back(i);
        }

        for (int i = 1; i < N; i++) {
            vector<int> temp;
            for (int num : result) {
                if (num == 0) {
                    continue;
                }

                int last = num % 10;
                if (last + K <= 9) {
                    temp.push_back(num * 10 + last + K);
                }
                if (K != 0 and last - K >= 0) { // if K == 0, we should not count it twice
                    temp.push_back(num * 10 + last - K);
                }
            }
            result = temp;
        }
        return result;
    }
};
