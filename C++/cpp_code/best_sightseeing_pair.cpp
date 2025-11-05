/*
1021. Best Sightseeing Pair
https://leetcode.com/problems/best-sightseeing-pair/

Given an array A of positive integers,
A[i] represents the value of the i-th sightseeing spot,
and two sightseeing spots i and j have distance j - i between them.

The score of a pair (i < j) of sightseeing spots is (A[i] + A[j] + i - j):
the sum of the values of the sightseeing spots, minus the distance between them.

Return the maximum score of a pair of sightseeing spots.

Example 1:
Input: [8,1,5,2,6]
Output: 11
Explanation: i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11

Note:
2 <= A.length <= 50000
1 <= A[i] <= 1000
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
    int maxScoreSightseeingPair(vector<int> &A) {
        int result = A[0];
        int curMax = A[0];
        for (int i = 1; i < A.size(); i++) {
            result = max(result, curMax - 1 + A[i]);
            curMax = max(A[i], curMax - 1);
        }
        return result;
    }
};