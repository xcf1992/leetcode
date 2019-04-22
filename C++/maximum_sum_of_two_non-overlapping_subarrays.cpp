/*
 1031. Maximum Sum of Two Non-Overlapping Subarrays
 Given an array A of non-negative integers, return the maximum sum of elements in two non-overlapping (contiguous) subarrays, which have lengths L and M.  (For clarification, the L-length subarray could occur before or after the M-length subarray.)
 
 Formally, return the largest V for which V = (A[i] + A[i+1] + ... + A[i+L-1]) + (A[j] + A[j+1] + ... + A[j+M-1]) and either:
 
 0 <= i < i + L - 1 < j < j + M - 1 < A.length, or
 0 <= j < j + M - 1 < i < i + L - 1 < A.length.
 
 
 Example 1:
 
 Input: A = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
 Output: 20
 Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
 Example 2:
 
 Input: A = [3,8,1,3,2,1,8,9,0], L = 3, M = 2
 Output: 29
 Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.
 Example 3:
 
 Input: A = [2,1,5,6,0,9,5,0,3,8], L = 4, M = 3
 Output: 31
 Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [3,8] with length 3.
 
 
 Note:
 
 L >= 1
 M >= 1
 L + M <= A.length <= 1000
 0 <= A[i] <= 1000
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
        int n = A.size();
        vector<int> sum(n, 0);
        sum[0] = A[0];
        for (int i = 1; i < n; ++i) {
            sum[i] = sum[i - 1] + A[i];
        }
        
        int result = sum[L + M - 1];
        int Lmax = sum[L - 1]; // max sum of contiguous L elements before the last M elements.
        int Mmax = sum[M - 1]; // max sum of contiguous M elements before the last L elements.
        for (int i = L + M; i < n; ++i) {
            Lmax = max(Lmax, sum[i - M] - sum[i - L - M]);
            Mmax = max(Mmax, sum[i - L] - sum[i - L - M]);
            result = max(result, max(Lmax + sum[i] - sum[i - M], Mmax + sum[i] - sum[i - L]));
        }
        return result;
    }
};

/* wrong answer
 [8,20,6,2,20,17,6,3,20,8,12]
 5
 4
 */
class Solution1 {
private:
    vector<int> getMax(vector<int>& A, int start, int end, int length) {
        if (end - start < length) {
            return {};
        }
        
        vector<int> result(3, 0);
        for (int i = start; i < start + length; ++i) {
            result[2] += A[i];
        }
        result[0] = start;
        result[1] = start + length - 1;
        
        int cur = result[2];
        for (int i = start + length; i < end; ++i) {
            int temp = cur + A[i] - A[i - length];
            if (temp > result[2]) {
                result[2] = temp;
                result[0] = i - length + 1;
                result[1] = i;
            }
            cur = temp;
        }
        return result;
    }
    
    int getMaxSum(vector<int>& A, int L, int M) {
        int n = A.size();
        vector<int> maxL = getMax(A, 0, n, L);
        vector<int> maxM1 = getMax(A, 0, maxL[0], M);
        vector<int> maxM2 = getMax(A, maxL[1] + 1, n, M);
        int result = INT_MIN;
        if (!maxM1.empty()) {
            result = max(result, maxL[2] + maxM1[2]);
        }
        if (!maxM2.empty()) {
            result = max(result, maxL[2] + maxM2[2]);
        }
        return result;
    }
public:
    int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
        return max(getMaxSum(A, L, M), getMaxSum(A, M, L));
    }
};
