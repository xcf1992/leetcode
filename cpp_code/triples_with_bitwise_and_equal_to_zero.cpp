/*
982. Triples with Bitwise AND Equal To Zero

Given an array of integers A,
find the number of triples of indices (i, j, k) such that:
0 <= i < A.length
0 <= j < A.length
0 <= k < A.length
A[i] & A[j] & A[k] == 0, where & represents the bitwise-AND operator.

Example 1:
Input: [2,1,3]
Output: 12
Explanation: We could choose the following i, j, k triples:
(i=0, j=0, k=1) : 2 & 2 & 1
(i=0, j=1, k=0) : 2 & 1 & 2
(i=0, j=1, k=1) : 2 & 1 & 1
(i=0, j=1, k=2) : 2 & 1 & 3
(i=0, j=2, k=1) : 2 & 3 & 1
(i=1, j=0, k=0) : 1 & 2 & 2
(i=1, j=0, k=1) : 1 & 2 & 1
(i=1, j=0, k=2) : 1 & 2 & 3
(i=1, j=1, k=0) : 1 & 1 & 2
(i=1, j=2, k=0) : 1 & 3 & 2
(i=2, j=0, k=1) : 3 & 2 & 1
(i=2, j=1, k=0) : 3 & 1 & 2

Note:
1 <= A.length <= 1000
0 <= A[i] < 2^16
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
/*
Using vector to store the occurrence of the first 2 value's AND result (A[i] & A[j]).
For all A[k], check all values between 0 and (1 << 16).
If the value AND A[k] is equal to 0, then add the occurrence of this value from step 1 to result.

Trick:
We don't have to go through (0 ~ 1 << 16) to find the answer.
If (A[k] & X) != 0, we can skip next (A[i] & X) - 1 values and still get correct result.

For example:
Assume A[k] is 0x11000 and X is 0x1000.
Obviously, the next (0x1000 - 1) values (0x1001 to 0x1111) will not meet the requirement.
*/
class Solution {
public:
    int countTriplets(vector<int>& A) {
        int n = A.size();
        vector<int> dp(1 << 16);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[A[i] & A[j]] += 1;
            }
        }

        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (1 << 16); j++) {
                if ((A[i] & j) == 0) {
                    result += dp[j];
                }
                else {
                    j += (A[i] & j) - 1;
                }
            }
        }
        return result;
    }
};

class Solution1 {
public:
    int countTriplets(vector<int>& A) {
        int n = A.size();
        vector<int> count(1 << 16);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                count[A[i] & A[j]] += 1;
            }
        }

        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (1 << 16); j++) if ((A[i] & j) == 0) {
                result += count[j];
            }
        }
        return result;
    }
};
