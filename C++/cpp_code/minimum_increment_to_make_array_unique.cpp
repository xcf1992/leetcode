/*
945. Minimum Increment to Make Array Unique
https://leetcode.com/problems/minimum-increment-to-make-array-unique/

Given an array of integers A,
a move consists of choosing any A[i], and incrementing it by 1.
Return the least number of moves to make every value in A unique.

Example 1:
Input: [1,2,2]
Output: 1
Explanation:  After 1 move, the array could be [1, 2, 3].

Example 2:
Input: [3,2,1,2,1,7]
Output: 6
Explanation:  After 6 moves, the array could be [3, 4, 1, 2, 5, 7].
It can be shown with 5 or less moves that it is impossible for the array to have all unique values.

Note:
0 <= A.length <= 40000
0 <= A[i] < 40000
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
    int minIncrementForUnique(vector<int>& A) {
        vector<int> count(100000, 0);
        for (int num : A) {
            count[num] += 1;
        }

        int result = 0;
        for (int i = 0; i < count.size(); ++i) {
            if (count[i] > 1) {
                result += count[i] - 1;
                count[i + 1] += count[i] - 1;
            }
        }
        return result;
    }
};

class Solution1 {
public:
    int minIncrementForUnique(vector<int>& A) {
        if (A.empty()) {
            return 0;
        }

        sort(A.begin(), A.end());
        int result = 0;
        int curMin = A[0];
        for (int i = 1; i < A.size(); i++) {
            if (A[i] <= curMin) {
                result += curMin + 1 - A[i];
                A[i] = curMin + 1;
            }
            curMin = A[i];
        }
        return result;
    }
};