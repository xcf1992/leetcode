/*
961. N-Repeated Element in Size 2N Array
In a array A of size 2N, there are N+1 unique elements, and exactly one of these elements is repeated N times.

Return the element repeated N times.

Example 1:

Input: [1,2,3,3]
Output: 3
Example 2:

Input: [2,1,2,5,3,2]
Output: 2
Example 3:

Input: [5,1,5,2,5,3,5,4]
Output: 5


Note:

4 <= A.length <= 10000
0 <= A[i] < 10000
A.length is even
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
If we ever find a repeated element, it must be the answer. Let's call this answer the major element.

Consider all subarrays of length 4. There must be a major element in at least one such subarray.

This is because either:

There is a major element in a length 2 subarray, or;
Every length 2 subarray has exactly 1 major element,
which means that a length 4 subarray that begins at a major element will have 2 major elements.
*/
class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        int n = A.size();
        for (int i = 0; i < n - 3; ++i) {
            if (A[i] == A[i + 1] or A[i] == A[i + 2] or A[i] == A[i + 3]) {
                return A[i];
            }
            if (A[i + 1] == A[i + 2] or A[i + 1] == A[i + 3]) {
                return A[i + 1];
            }
            if (A[i + 2] == A[i + 3]) {
                return A[i + 2];
            }
        }
        return -1;
    }
};
