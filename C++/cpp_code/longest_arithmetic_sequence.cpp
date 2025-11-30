/*
1027. Longest Arithmetic Sequence
https://leetcode.com/problems/longest-arithmetic-sequence/

Given an array A of integers,
return the length of the longest arithmetic subsequence in A.

Recall that a subsequence of A is a list A[i_1], A[i_2], ..., A[i_k] with 0 <= i_1 < i_2 < ... < i_k <= A.length - 1,
and that a sequence B is arithmetic if B[i+1] - B[i] are all the same value (for 0 <= i < B.length - 1).

Example 1:
Input: [3,6,9,12]
Output: 4
Explanation:
The whole array is an arithmetic sequence with steps of length = 3.

Example 2:
Input: [9,4,7,2,10]
Output: 3
Explanation:
The longest arithmetic subsequence is [4,7,10].

Example 3:
Input: [20,1,15,3,10,5,8]
Output: 4
Explanation:
The longest arithmetic subsequence is [20,15,10,5].

Note:
2 <= A.length <= 2000
0 <= A[i] <= 10000
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
    int longestArithSeqLength(vector<int>& A) {
        int result = 1;
        int n = A.size();
        vector<unordered_map<int, int>> dp(n);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int gap = A[i] - A[j];
                if (dp[j].find(gap) == dp[j].end()) {
                    dp[i][gap] = 2;
                } else {
                    dp[i][gap] = max(dp[i][gap], 1 + dp[j][gap]);
                }
                result = max(result, dp[i][gap]);
            }
        }
        return result;
    }
};