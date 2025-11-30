/*
 908. Smallest Range I
 Given an array A of integers, for each integer A[i] we may choose any x with -K <= x <= K, and add x to A[i].

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
 Output: 0
 Explanation: B = [3,3,3] or B = [4,4,4]


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
#include <climits>
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    int smallestRangeI(vector<int>& A, int K) {
        int curMin = INT_MAX;
        int curMax = INT_MIN;
        for (int num : A) {
            curMin = min(num, curMin);
            curMax = max(num, curMax);
        }
        int gap = curMax - curMin;
        return max(0, gap - 2 * K);
    }
};

class Solution1 {
public:
    int smallestRangeI(vector<int>& A, int K) {
        int result = 0;
        int curMin = A[0] - K;
        int curMax = A[0] + K;
        for (int i = 1; i < A.size(); i++) {
            int newMin = A[i] - K;
            int newMax = A[i] + K;
            if (result == 0) {
                if (newMin > curMax or newMax < curMin) {
                    if (curMin > newMax) {
                        curMax = curMin;
                        curMin = newMax;
                    } else {
                        curMin = curMax;
                        curMax = newMin;
                    }
                    result = curMax - curMin;
                } else {
                    curMin = max(newMin, curMin);
                    curMax = min(newMax, curMax);
                }
            } else {
                if (newMin > curMax) {
                    curMax = newMin;
                } else if (newMax < curMin) {
                    curMin = newMax;
                }
                result = curMax - curMin;
            }
        }
        return result;
    }
};