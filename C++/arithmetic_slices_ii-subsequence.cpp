/*
 446. Arithmetic Slices II - Subsequence
 A sequence of numbers is called arithmetic if it consists of at least three elements
 and if the difference between any two consecutive elements is the same.

 For example, these are arithmetic sequences:
 1, 3, 5, 7, 9
 7, 7, 7, 7
 3, -1, -5, -9

 The following sequence is not arithmetic.
 1, 1, 2, 5, 7

 A zero-indexed array A consisting of N numbers is given.
 A subsequence slice of that array is any sequence of integers (P0, P1, ..., Pk) such that 0 ≤ P0 < P1 < ... < Pk < N.

 A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic
 if the sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic.
 In particular, this means that k ≥ 2.

 The function should return the number of arithmetic subsequence slices in the array A.

 The input contains N integers.
 Every integer is in the range of -2^31 and 2^31-1 and 0 ≤ N ≤ 1000.
 The output is guaranteed to be less than 231-1.

 Example:

 Input: [2, 4, 6, 8, 10]

 Output: 7

 Explanation:
 All arithmetic subsequence slices are:
 [2,4,6]
 [4,6,8]
 [6,8,10]
 [2,4,6,8]
 [4,6,8,10]
 [2,4,6,8,10]
 [2,6,10]
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
I think the idea is to store the diff and number of times this diff has appeared before in a hash map for each element;
And we only calculate the diff between current element and the element before current.
for example:
[2] stores a empty hashmap
[2,4] now 4 stores a mapentry [2,1] because 4-2 = 2,and for element 2 stores nothing
[2,4,6] 6-4 =2 and since element 4 stores[2,1], which means diff 2 has appeared once before,
so count = 1 and we put [2,2] in 6. Also 6-2 = 4, we put [4,1] in 6;
*/
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        if (n < 3) {
            return 0;
        }

        int result = 0;
        vector<unordered_map<long long, int>> dp(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; j++) {
                long long gap = (long long)A[i] - (long long)A[j];
                dp[i][gap] += 1;
                if (dp[j].find(gap) != dp[j].end()) {
                    /*
                    * if there are subsequence end at j with gap, add together,
                    * which ensure there are at least three elements in this arithmetic sequence
                    */
                    dp[i][gap] += dp[j][gap];
                    result += dp[j][gap];
                }
            }
        }
        return result;
    }
};
