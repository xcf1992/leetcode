/*
 An array is monotonic if it is either monotone increasing or monotone decreasing.

 An array A is monotone increasing if for all i <= j, A[i] <= A[j].  An array A is monotone decreasing if for all i <=
 j, A[i] >= A[j].

 Return true if and only if the given array A is monotonic.



 Example 1:

 Input: [1,2,2,3]
 Output: true
 Example 2:

 Input: [6,5,4,4]
 Output: true
 Example 3:

 Input: [1,3,2]
 Output: false
 Example 4:

 Input: [1,2,4,5]
 Output: true
 Example 5:

 Input: [1,1,1]
 Output: true


 Note:

 1 <= A.length <= 50000
 -100000 <= A[i] <= 100000
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
    bool isMonotonic(vector<int>& A) {
        if (A.size() <= 2) {
            return true;
        }

        int i = 0;
        while (i + 1 < A.size() and A[i] == A[i + 1]) {
            i += 1;
        }
        bool increase = true;
        if (i + 1 < A.size() and A[i] > A[i + 1]) {
            increase = false;
            i += 1;
        }
        while (i + 1 < A.size()) {
            if (A[i] < A[i + 1]) {
                if (!increase) {
                    return false;
                }
            } else if (A[i] > A[i + 1]) {
                if (increase) {
                    return false;
                }
            }
            i += 1;
        }
        return true;
    }
};