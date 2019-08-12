/*
 1005. Maximize Sum Of Array After K Negations
 Given an array A of integers,
 we must modify the array in the following way:
 we choose an i and replace A[i] with -A[i],
 and we repeat this process K times in total.
 (We may choose the same index i multiple times.)

 Return the largest possible sum of the array after modifying it in this way.

 Example 1:

 Input: A = [4,2,3], K = 1
 Output: 5
 Explanation: Choose indices (1,) and A becomes [4,-2,3].
 Example 2:

 Input: A = [3,-1,0,2], K = 3
 Output: 6
 Explanation: Choose indices (1, 2, 2) and A becomes [3,1,0,2].
 Example 3:

 Input: A = [2,-3,-1,5,-4], K = 2
 Output: 13
 Explanation: Choose indices (1, 4) and A becomes [2,3,-1,5,4].


 Note:

 1 <= A.length <= 10000
 1 <= K <= 10000
 -100 <= A[i] <= 100
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
    int largestSumAfterKNegations(vector<int>& A, int K) {
        sort(A.begin(), A.end());
        for (int i = 0; i < A.size() and K > 0 and A[i] < 0; i++) {
            A[i] = 0 - A[i];
            K--;
        }
        int result = 0;
        int minN = INT_MAX;
        for (int a : A) {
            result += a;
            minN = min(minN, a);
        }
        return result - (K % 2) * minN * 2;
    }
};
