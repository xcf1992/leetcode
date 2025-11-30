/*
873. Length of Longest Fibonacci Subsequence
https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/

A sequence X_1, X_2, ..., X_n is fibonacci-like if:
n >= 3
X_i + X_{i+1} = X_{i+2} for all i + 2 <= n
Given a strictly increasing array A of positive integers forming a sequence,
find the length of the longest fibonacci-like subsequence of A.  If one does not exist, return 0.

(Recall that a subsequence is derived from another sequence A by deleting any number of elements (including none) from
A, without changing the order of the remaining elements. For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].)

Example 1:
Input: [1,2,3,4,5,6,7,8]
Output: 5
Explanation:
The longest subsequence that is fibonacci-like: [1,2,3,5,8].

Example 2:
Input: [1,3,7,11,12,14,18]
Output: 3
Explanation:
The longest subsequence that is fibonacci-like:
[1,11,12], [3,11,14] or [7,11,18].

Note:
3 <= A.length <= 1000
1 <= A[0] < A[1] < ... < A[A.length - 1] <= 10^9
(The time limit has been reduced by 50% for submissions in Java, C, and C++.)
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
#include <climits>
#include <set>
using namespace std;
/*
dp[a, b] represents the length of fibo sequence ends up with (a, b)
Then we have dp[a, b] = (dp[b - a, a] + 1 ) or 2
The complexity reduce to O(N^2).
In C++/Java, I use 2D dp and index as key.
In Python, I use value as key.
*/
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        int n = A.size();
        if (n < 3) {
            return 0;
        }

        unordered_map<int, int> index;
        for (int i = 0; i < n; ++i) {
            index[A[i]] = i;
        }

        int result = 0;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < j; ++i) {
                int diff = A[j] - A[i];
                if (diff < A[i] and index.find(diff) != index.end()) {
                    dp[i][j] = dp[index[diff]][i] + 1;
                } else {
                    dp[i][j] = 2;
                }
                result = max(result, dp[i][j]);
            }
        }
        return result > 2 ? result : 0;
    }
};

class Solution1 {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        int n = A.size();
        if (n < 3) {
            return 0;
        }

        int result = 0;
        unordered_set<int> num(A.begin(), A.end());
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int first = A[i];
                int second = A[j];
                int length = 2;
                while (num.find(first + second) != num.end()) {
                    length += 1;
                    second += first;
                    first = second - first;
                }
                result = max(result, length);
            }
        }
        return result > 2 ? result : 0;
    }
};