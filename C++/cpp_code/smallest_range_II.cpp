/*
910. Smallest Range II
Given an array A of integers, for each integer A[i] we need to choose either x = -K or x = K, and add x to A[i] (only once).

After this process, we have some array B.

Return the smallest possible difference between the maximum value of B and the minimum value of B.



Example 1:

Input: A = [1], K = 0
Output: 0
Explanation: B = [1]
Example 2:

Input: A = [0,10], K = 2
Output: 6
Explanation: B = [2,8]
Example 3:

Input: A = [1,3,6], K = 3
Output: 3
Explanation: B = [4,6,3]


Note:

1 <= A.length <= 10000
0 <= A[i] <= 10000
0 <= K <= 10000
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
Intuition:
For each integer A[i],
we may choose either x = -K or x = K.

If we add K to all B[i], the result won't change.

It's the same as:
For each integer A[i], we may choose either x = 0 or x = 2 * K.

Explanation:
We sort the A first, and we choose to add x = 0 to all A[i].
Now we have res = A[n - 1] - A[0].

Starting from the smallest of A, we add 2 * K to A[i],
hoping this process will reduce the difference.

Update the new mx = max(mx, A[i] + 2 * K)
Update the new mn = min(A[i + 1], A[0] + 2 * K)
Update the res = min(res, mx - mn)

Time Complexity:
O(NlogN), in both of the worst and the best cases.
In the Extending Reading part, I improve this to O(N) in half of cases.

The intuition is you want make smaller number bigger, and bigger number smaller.
Which is first half + K, second half - K in a sorting array.

all the elements to be added 2K must be the left continuous part of the array ([True, ..., True, False, ... False]).
It can be proved that if in the best solution there are some elements added by 0 between the ones added by 2K,
we can add 2K to them, and this operation will not make the solution worse. Then we can find where the split it is in one pass.
*/
class Solution {
public:
    int smallestRangeII(vector<int>& A, int K) {
        sort(A.begin(), A.end());
        int curMax = A.back();
        int curMin = A.front();
        int result = curMax - curMin;
        for (int i = 0; i < A.size() - 1; i++) {
            curMax = max(curMax, A[i] + 2 * K);
            curMin = min(A[i + 1], A[0] + 2 * K);
            result = min(result, curMax - curMin);
        }
        return result;
    }
};

class Solution1 {
public:
    int smallestRangeII(vector<int>& A, int K) {
        int curMin = INT_MAX;
        int curMax = INT_MIN;
        for (int num : A) {
            curMin = min(num, curMin);
            curMax = max(num, curMax);
        }
        if (curMax - curMin > K) {
            curMin = min(curMin + K, curMax - K);
            curMax = max(curMin + K, curMax - K);
        }
        int result = curMax - curMin;
        for (int num : A) {
            if (num + K <= curMax and num + K >= curMin) {
                continue;
            }
            if (num - K <= curMax and num - K >= curMin) {
                continue;
            }
            int newMin = num - K;
            int newMax = num + K;
            if (newMax < curMin) {
                curMin = newMax;
            }
            else if (newMin > curMax) {
                curMax = newMin;
            }
            else if (newMin < curMin and newMax > curMax) {
                if (newMax - curMin > curMax - newMin) {
                    curMin = newMin;
                }
                else {
                    curMax = newMax;
                }
            }
            result = curMax - curMin;
        }
        return result;
    }
};
