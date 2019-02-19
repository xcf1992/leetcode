/*
 992. Subarrays with K Different Integers

 Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of A good if the number of different integers in that subarray is exactly K.
 
 (For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)
 
 Return the number of good subarrays of A.
 
 
 
 Example 1:
 
 Input: A = [1,2,1,2,3], K = 2
 Output: 7
 Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
 Example 2:
 
 Input: A = [1,2,1,3,4], K = 3
 Output: 3
 Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
 
 
 Note:
 
 1 <= A.length <= 20000
 1 <= A[i] <= A.length
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
 Write a helper using sliding window,
 to get the number of subarrays with at most K distinct elements.
 Then f(exactly K) = f(atMost K) - f(atMost K-1).
 
 Of course, you can merge 2 for loop into ones, if you like.
 */
class Solution {
private:
    int atMostK(vector<int>& A, int K) {
        int result = 0;
        int start = 0;
        unordered_map<int, int> count;
        for (int end = 0; end < A.size(); end++) {
            if (count[A[end]] == 0) {
                K -= 1;
            }
            count[A[end]] += 1;
            while (K < 0) {
                count[A[start]] -= 1;
                if (count[A[start]] == 0) {
                    K += 1;
                }
                start += 1;
            }
            // subarrays with at most K different elements, and the subarray end with end
            result += end - start + 1;
        }
        return result;
    }
public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        return atMostK(A, K) - atMostK(A, K - 1);
    }
};
