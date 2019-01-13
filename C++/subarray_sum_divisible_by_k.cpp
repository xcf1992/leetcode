/*
 Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.
 
 
 
 Example 1:
 
 Input: A = [4,5,0,-2,-3,1], K = 5
 Output: 7
 Explanation: There are 7 subarrays with a sum divisible by K = 5:
 [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
 
 
 Note:
 
 1 <= A.length <= 30000
 -10000 <= A[i] <= 10000
 2 <= K <= 10000
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
    int subarraysDivByK(vector<int>& A, int K) {
        int n = A.size();
        vector<int> mod(K, 0);
        int curSum = 0;
        for (int i = 0; i < n; i++) {
            curSum += A[i];
            mod[((curSum % K) + K) % K] += 1;
        }
        
        int result = 0;
        for (int i = 0; i < K; i++) {
            if (mod[i] > 1) {
                result += (mod[i] * (mod[i] - 1)) / 2;
            }
        }
        return result + mod[0];
    }
};
