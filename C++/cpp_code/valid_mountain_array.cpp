/*
 Given an array A of integers, return true if and only if it is a valid mountain array.

 Recall that A is a mountain array if and only if:

 A.length >= 3
 There exists some i with 0 < i < A.length - 1 such that:
 A[0] < A[1] < ... A[i-1] < A[i]
 A[i] > A[i+1] > ... > A[B.length - 1]


 Example 1:

 Input: [2,1]
 Output: false
 Example 2:

 Input: [3,5,5]
 Output: false
 Example 3:

 Input: [0,3,2,1]
 Output: true


 Note:

 0 <= A.length <= 10000
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
#include <stdio.h>
#include <map>
#include <numeric>
using namespace std;

class Solution {
private:
    bool isDecreasing(vector<int> &A, int start) {
        if (start >= A.size() - 1) {
            return false;
        }

        for (int i = start; i < A.size() - 1; i++) {
            if (A[i] <= A[i + 1]) {
                return false;
            }
        }
        return true;
    }

public:
    bool validMountainArray(vector<int> &A) {
        if (A.size() < 3) {
            return false;
        }
        int climax = 0;
        while (climax < A.size() - 1) {
            if (A[climax] < A[climax + 1]) {
                climax += 1;
            } else {
                break;
            }
        }
        if (climax == 0) {
            return false;
        }
        return isDecreasing(A, climax);
    }
};