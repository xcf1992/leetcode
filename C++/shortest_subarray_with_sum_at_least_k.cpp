/*
 862. Shortest Subarray with Sum at Least K

 Return the length of the shortest, non-empty, contiguous subarray of A with sum at least K.

 If there is no non-empty subarray with sum at least K, return -1.

 Example 1:

 Input: A = [1], K = 1
 Output: 1
 Example 2:

 Input: A = [1,2], K = 4
 Output: -1
 Example 3:

 Input: A = [2,-1,2], K = 3
 Output: 3


 Note:

 1 <= A.length <= 50000
 -10 ^ 5 <= A[i] <= 10 ^ 5
 1 <= K <= 10 ^ 9
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
 We can rephrase this as a problem about the prefix sums of A. Let P[i] = A[0] + A[1] + ... + A[i-1].
 We want the smallest y-x such that y > x and P[y] - P[x] >= K.

 Motivated by that equation, let opt(y) be the largest x such that P[x] <= P[y] - K. We need two key observations:

 If x1 < x2 and P[x2] <= P[x1],
 then opt(y) can never be x1,
 as if P[x1] <= P[y] - K,
 then P[x2] <= P[x1] <= P[y] - K but y - x2 is smaller.
 This implies that our candidates x for opt(y) will have increasing values of P[x].

 If opt(y1) = x,
 then we do not need to consider this x again.
 For if we find some y2 > y1
 with opt(y2) = x,
 then it represents an answer of y2 - x which is worse (larger) than y1 - x.

 Algorithm

 Maintain a "monoqueue" of indices of P:
 a deque of indices x_0, x_1, ...
 such that P[x_0], P[x_1], ... is increasing.

 When adding a new index y,
 we'll pop x_i from the end of the deque
 so that P[x_0], P[x_1], ..., P[y] will be increasing.

 If P[y] >= P[x_0] + K,
 then (as previously described),
 we don't need to consider this x_0 again,
 and we can pop it from the front of the deque.
 ====================================================-====================================================
 Calculate prefix sum B of list A.
 B[j] - B[i] represents the sum of subarray A[i] ~ A[j-1]
 Deque d will keep indexes of increasing B[i].
 For every B[i], we will compare B[i] - B[d[0]] with K.

 Time Complexity:
 Loop on B O(N)
 Every index will be pushed only once into deque. O(N)

 Q: How to think of such solutions?
 A: Basic idea, for array starting at every A[i], find the shortest one with sum at leat K.
 In my solution, for B[i], find the smallest j that B[j] - B[i] >= K.
 Keep this in mind for understanding two while loops.

 Q: What is the purpose of first while loop?
 A: For the current prefix sum B[i], it covers all subarray ending at A[i-1].
 We want know if there is a subarray, which starts from an index, ends at A[i-1] and has at least sum K.
 So we start to compare B[i] with the smallest prefix sum in our deque, which is B[D[0]], hoping that [i] - B[d[0]] >= K.
 So if B[i] - B[d[0]] >= K, we can update our result res = min(res, i - d.popleft()).
 The while loop helps compare one by one, until this condition isn't valid anymore.

 Q: Why we pop left in the first while loop?
 A: This the most tricky part that improve my solution to get only O(N).
 D[0] exists in our deque, it means that before B[i], we didn't find a subarray whose sum at least K.
 B[i] is the first prefix sum that valid this condition.
 In other words, A[D[0]] ~ A[i-1] is the shortest subarray starting at A[D[0]] with sum at least K.
 We have already find it for A[D[0]] and it can't be shorter, so we can drop it from our deque.

 Q: What is the purpose of second while loop?
 A: To keep B[D[i]] increasing in the deque.

 Q: Why keep the deque increase?
 A: If B[i] <= B[d.back()] and moreover we already know that i > d.back(), it means that compared with d.back(),
 B[i] can help us make the subarray length shorter and sum bigger. So no need to keep d.back() in our deque.
 */
class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        int n = A.size();
        vector<int> preSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            preSum[i + 1] = preSum[i] + A[i];
        }

        int result = n + 1;
        deque<int> monoQ;
        for (int i = 0; i <= n; i++) {
            while (!monoQ.empty() and preSum[i] - preSum[monoQ.front()] >= K) {
                result = min(result, i - monoQ.front());
                monoQ.pop_front();
            }
            /*
             * if with i >= monoQ.back() and preSum[i] <= preSum[monoQ.back()]
             * then it will always better to pick i to have a shorter subarray
            */
            while (!monoQ.empty() and preSum[i] <= preSum[monoQ.back()]) {
                monoQ.pop_back();
            }
            monoQ.push_back(i);
        }
        return result == n + 1 ? -1 : result;
    }
};
