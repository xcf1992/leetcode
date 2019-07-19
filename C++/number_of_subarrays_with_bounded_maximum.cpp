/*
 795. Number of Subarrays with Bounded Maximum
 We are given an array A of positive integers,
 and two positive integers L and R (L <= R).

 Return the number of (contiguous, non-empty) subarrays
 such that the value of the maximum array element in that subarray is at least L and at most R.

 Example :
 Input:
 A = [2, 1, 4, 3]
 L = 2
 R = 3
 Output: 3
 Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
 Note:

 L, R  and A[i] will be an integer in the range [0, 10^9].
 The length of A will be in the range of [1, 50000].
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
#include <set>
using namespace std;

class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        int result = 0;
        int dp = 0;
        int start = -1;
        for (int i = 0; i < A.size(); i++) {
            if (A[i] > R) {
                dp = 0;
                start = i;
                continue;
            }
            if (A[i] >= L) {
                dp = i - start;
            }
            result += dp;
        }
        return result;
    }
};

class Solution1 {
public:
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        int result = 0;
        int dp = 0;
        int start = -1;
        for (int i = 0; i < A.size(); i++) {
            if (A[i] < L) {
                result += dp;
            }
            else if (A[i] > R) {
                dp = 0;
                start = i;
            }
            else {
                dp = i - start;
                result += dp;
            }
        }
        return result;
    }
};