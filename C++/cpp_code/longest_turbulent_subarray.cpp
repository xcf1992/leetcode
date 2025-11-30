/*
978. Longest Turbulent Subarray
https://leetcode.com/problems/longest-turbulent-subarray/

A subarray A[i], A[i+1], ..., A[j] of A is said to be turbulent if and only if:

For i <= k < j,
A[k] > A[k+1] when k is odd,
and A[k] < A[k+1] when k is even;
OR,
for i <= k < j,
A[k] > A[k+1] when k is even,
and A[k] < A[k+1] when k is odd.
That is, the subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.

Return the length of a maximum size turbulent subarray of A.

Example 1:

Input: [9,4,2,10,7,8,8,1,9]
Output: 5
Explanation: (A[1] > A[2] < A[3] > A[4] < A[5])
Example 2:

Input: [4,8,12,16]
Output: 2
Example 3:

Input: [100]
Output: 1


Note:

1 <= A.length <= 40000
0 <= A[i] <= 10^9
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
#include <numeric>
using namespace std;

class Solution {
public:
    int maxTurbulenceSize(vector<int>& A) {
        int n = A.size();
        if (n <= 1) {
            return n;
        }

        int result = 1;
        int increase = 1;
        int decrease = 1;
        for (int i = 1; i < n; ++i) {
            if (A[i - 1] < A[i]) {
                increase = decrease + 1;
                decrease = 1;
            } else if (A[i - 1] > A[i]) {
                decrease = increase + 1;
                increase = 1;
            } else {
                increase = 1;
                decrease = 1;
            }
            result = max(result, max(increase, decrease));
        }
        return result;
    }
};

class Solution1 {
public:
    int maxTurbulenceSize(vector<int>& A) {
        int n = A.size();
        if (n <= 1) {
            return n;
        }

        vector<int> change;
        for (int i = 1; i < n; i++) {
            if (A[i] > A[i - 1]) {
                change.push_back(1);
            } else if (A[i] < A[i - 1]) {
                change.push_back(-1);
            } else {
                change.push_back(0);
            }
        }

        int result = 0;
        int cur = change[0] == 0 ? 0 : 1;
        for (int i = 1; i < change.size(); i++) {
            if (change[i] == 0 or change[i] == change[i - 1]) {
                result = max(cur, result);
                cur = change[i] == 0 ? 0 : 1;
            } else {
                cur += 1;
            }
        }
        return max(result, cur) + 1;
    }
};