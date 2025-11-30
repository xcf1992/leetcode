/*
852. Peak Index in a Mountain Array

Let's call an array A a mountain if the following properties hold:
A.length >= 3
There exists some 0 < i < A.length - 1 such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1]
Given an array that is definitely a mountain,
return any i such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1].

Example 1:
Input: [0,1,0]
Output: 1

Example 2:
Input: [0,2,1,0]
Output: 1

Note:
3 <= A.length <= 10000
0 <= A[i] <= 10^6
A is a mountain, as defined above.
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
using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        int lo = 0;
        int hi = A.size() - 1;
        while (lo < hi) {
            int mi = lo + (hi - lo) / 2;
            if (A[mi] < A[mi + 1]) {
                lo = mi + 1;
            } else {
                hi = mi;
            }
        }
        return lo;
    }
};

class Solution1 {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        int n = A.size();
        int left = 0;
        int right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mid - 1 >= 0 and A[mid] > A[mid - 1] and mid + 1 <= n - 1 and A[mid] > A[mid + 1]) {
                return mid;
            }

            if (mid - 1 >= 0 and A[mid] > A[mid - 1]) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return 0;
    }
};