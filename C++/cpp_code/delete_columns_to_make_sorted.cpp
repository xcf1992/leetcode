/*
944. Delete Columns to Make Sorted

We are given an array A of N lowercase letter strings, all of the same length.
Now, we may choose any set of deletion indices,
and for each string,
we delete all the characters in those indices.

For example,
if we have a string "abcdef" and deletion indices {0, 2, 3},
then the final string after deletion is "bef".

Suppose we chose a set of deletion indices D such that after deletions,
each remaining column in A is in sorted order.

Formally, the c-th column is [A[0][c], A[1][c], ..., A[A.length-1][c]]
Return the minimum possible value of D.length.

Example 1:
Input: ["cba","daf","ghi"]
Output: 1

Example 2:
Input: ["a","b"]
Output: 0

Example 3:
Input: ["zyx","wvu","tsr"]
Output: 3

Note:
1 <= A.length <= 100
1 <= A[i].length <= 1000
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
    int minDeletionSize(vector<string>& A) {
        int n = A.size();
        int m = A[0].size();
        int result = 0;
        for (int col = 0; col < m; col++) {
            for (int row = 1; row < n; row++) {
                if (A[row][col] < A[row - 1][col]) {
                    result += 1;
                    break;
                }
            }
        }
        return result;
    }
};