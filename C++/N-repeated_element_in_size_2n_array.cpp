/*
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

class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        int n1 = 0;
        int n2 = 1;
        int n3 = 2;
        int n4 = 3;
        while (n1 <= A.size() - 4) {
            if (A[n1] == A[n2] || A[n1] == A[n3] || A[n1] == A[n4]) {
                return A[n1];
            }
            if (A[n2] == A[n3] || A[n2] == A[n4]) {
                return A[n2];
            }
            if (A[n3] == A[n4]) {
                return A[n3];
            }

            n1 += 4;
            n2 += 4;
            n3 += 4;
            n4 += 4;
        }
        return -1;
    }
};