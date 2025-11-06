/*
1524. Number of Sub-arrays With Odd Sum
https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/

Given an array of integers arr.
Return the number of sub-arrays with odd sum.

As the answer may grow large,
the answer must be computed modulo 10^9 + 7.

Example 1:
Input: arr = [1,3,5]
Output: 4
Explanation: All sub-arrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
All sub-arrays sum are [1,4,9,3,8,5].
Odd sums are [1,9,3,5] so the answer is 4.

Example 2:
Input: arr = [2,4,6]
Output: 0
Explanation: All sub-arrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
All sub-arrays sum are [2,6,12,4,10,6].
All sub-arrays have even sum and the answer is 0.

Example 3:
Input: arr = [1,2,3,4,5,6,7]
Output: 16

Example 4:
Input: arr = [100,100,99,99]
Output: 4

Example 5:
Input: arr = [7]
Output: 1

Constraints:
1 <= arr.length <= 10^5
1 <= arr[i] <= 100
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int mod = 1e9 + 7;
        int result = 0;
        int oddSum = 0;
        int evenSum = 0;
        for (int num : arr) {
            if (num % 2 == 0) {
                evenSum = (evenSum + 1) % mod;
            } else {
                int temp = evenSum;
                evenSum = oddSum;
                oddSum = (temp + 1) % mod;
            }
            result = (result + oddSum) % mod;
        }
        return result;
    }
};