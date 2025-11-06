/*
845. Longest Mountain in Array
https://leetcode.com/problems/longest-mountain-in-array/

Let's call any (contiguous) subarray B (of A) a mountain if the following properties hold:
B.length >= 3
There exists some 0 < i < B.length - 1 such that B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
(Note that B could be any subarray of A, including the entire array A.)

Given an array A of integers,
return the length of the longest mountain.
Return 0 if there is no mountain.

Example 1:
Input: [2,1,4,7,3,2,5]
Output: 5
Explanation: The largest mountain is [1,4,7,3,2] which has length 5.

Example 2:
Input: [2,2,2]
Output: 0
Explanation: There is no mountain.

Note:
0 <= A.length <= 10000
0 <= A[i] <= 10000

Follow up:
Can you solve it using only one pass?
Can you solve it in O(1) space?
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
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
public:
    int longestMountain(vector<int>& A) {
        int n = A.size();
        if (n < 3) {
            return 0;
        }

        int result = 0;
        for (int i = 1; i < n - 1; i++) {
            if (A[i] > A[i - 1] and A[i] > A[i + 1]) {
                int left = i - 1;
                while (left > 0 and A[left] > A[left - 1]) {
                    left -= 1;
                }

                int right = i + 1;
                while (right < n - 1 and A[right] > A[right + 1]) {
                    right += 1;
                }
                result = max(result, right - left + 1);
            }
        }
        return result;
    }
};