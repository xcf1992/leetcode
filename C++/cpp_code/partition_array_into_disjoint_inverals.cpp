/*
915. Partition Array into Disjoint Intervals
https://leetcode.com/problems/partition-array-into-disjoint-intervals/

Given an array A, partition it into two (contiguous) subarrays left and right so that:
Every element in left is less than or equal to every element in right.
left and right are non-empty.
left has the smallest possible size.
Return the length of left after such a partitioning.
It is guaranteed that such a partitioning exists.

Example 1:
Input: [5,0,3,8,6]
Output: 3
Explanation: left = [5,0,3], right = [8,6]

Example 2:
Input: [1,1,1,0,6,12]
Output: 4
Explanation: left = [1,1,1,0], right = [6,12]

Note:
2 <= A.length <= 30000
0 <= A[i] <= 10^6
It is guaranteed there is at least one way to partition A as described.
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
    int partitionDisjoint(vector<int>& A) {
        int n = A.size();
        vector<int> leftMax(n, A.front());
        vector<int> rightMin(n, A.back());
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i - 1], A[i]);
            int j = n - 1 - i;
            rightMin[j] = min(rightMin[j + 1], A[j]);
        }

        for (int i = 0; i < n - 1; i++)
            if (leftMax[i] <= rightMin[i + 1]) {
                return i + 1;
            }
        return n;
    }
};