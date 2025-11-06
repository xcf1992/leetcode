/*
995. Minimum Number of K Consecutive Bit Flips

In an array A containing only 0s and 1s,
a K-bit flip consists of choosing a (contiguous) subarray of length K
and simultaneously changing every 0 in the subarray to 1,
and every 1 in the subarray to 0.

Return the minimum number of K-bit flips required so that there is no 0 in the array.
If it is not possible, return -1.

Example 1:
Input: A = [0,1,0], K = 1
Output: 2
Explanation: Flip A[0], then flip A[2].

Example 2:
Input: A = [1,1,0], K = 2
Output: -1
Explanation: No matter how we flip subarrays of size 2, we can't make the array become [1,1,1].

Example 3:
Input: A = [0,0,0,1,0,1,1,0], K = 3
Output: 3
Explanation:
Flip A[0],A[1],A[2]: A becomes [1,1,1,1,0,1,1,0]
Flip A[4],A[5],A[6]: A becomes [1,1,1,1,1,0,0,0]
Flip A[5],A[6],A[7]: A becomes [1,1,1,1,1,1,1,1]

Note:
1 <= A.length <= 30000
1 <= K <= A.length
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
/*
Intuition:
There is only one way to filp A[0],
and A[0] will tell us if we need to filp the range A[0] ~ A[K -1].
So we start from the leftmost one by one using a greedy idea to solve this problem.

Solution 1
Explanation
Create a new array isFlipped[n].
isFlipped[i] = 1 iff we flip K consecutive bits starting at A[i].

We maintain a variable flipped and flipped = 1 iff the current bit is flipped.

If flipped = 0 and A[i] = 0, we need to flip at A[i].
If flipped = 1 and A[i] = 1, we need to flip at A[i].

Complexity
O(N) time for one pass
O(N) extra space for isFlipped[n].
*/
class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        int n = A.size();
        int result = 0;
        vector<int> isFlipped(n, 0);
        int flipped = 0;
        for (int i = 0; i < n; ++i) {
            if (i >= K) {
                flipped ^= isFlipped[i - K];
            }
            if (flipped == A[i]) {
                if (i + K > n) {
                    return -1;
                }
                isFlipped[i] = 1;
                flipped ^= 1;
                result += 1;
            }
        }
        return result;
    }
};

class Solution1 {  // TLE
public:
    int minKBitFlips(vector<int>& A, int K) {
        int start = 0;
        int flips = 0;
        while (start <= A.size() - K) {
            if (A[start] == 0) {
                flips += 1;
                for (int i = start; i < start + K; i++) {
                    A[i] = 1 - A[i];
                }
            }
            start += 1;
        }

        for (int a : A) {
            if (a == 0) {
                return -1;
            }
        }
        return flips;
    }
};
