/*
1004. Max Consecutive Ones III
https://leetcode.com/problems/max-consecutive-ones-iii/

Given an array A of 0s and 1s, we may change up to K values from 0 to 1.
Return the length of the longest (contiguous) subarray that contains only 1s.

Example 1:
Input: A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
Output: 6
Explanation:
[1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1.
The longest subarray is underlined.

Example 2:
Input: A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
Output: 10
Explanation:
[0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.

Note:
1 <= A.length <= 20000
0 <= K <= A.length
A[i] is 0 or 1
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
    int longestOnes(vector<int>& A, int K) {
        int result = 0;
        int start = 0;
        int used = 0;
        int end = 0;
        int n = A.size();
        for (end = 0; end < n; ++end) {
            if (A[end] == 0) {
                used += 1;
            }
            while (used > K) {
                if (A[start] == 0) {
                    used -= 1;
                }
                start += 1;
            }
            result = max(result, end - start + 1);
        }
        return result;
    }
};