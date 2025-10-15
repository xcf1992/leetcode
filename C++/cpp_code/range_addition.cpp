/*
370. Range Addition
https://leetcode.com/problems/range-addition/

Assume you have an array of length n initialized with all 0's and are given k update operations.
Each operation is represented as a triplet: [startIndex, endIndex, inc]
which increments each element of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc.

Return the modified array after all k operations were executed.

Example:
Given:
length = 5,
updates = [
    [1,  3,  2],
    [2,  4,  3],
    [0,  2, -2]
]
Output:
[-2, 0, 3, 5, 3]
Explanation:
Initial state:
[ 0, 0, 0, 0, 0 ]
After applying operation [1, 3, 2]:
[ 0, 2, 2, 2, 0 ]
After applying operation [2, 4, 3]:
[ 0, 2, 5, 5, 3 ]
After applying operation [0, 2, -2]:
[-2, 0, 3, 5, 3 ]
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
using namespace std;

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> result(length, 0);
        for (int i = 0; i < updates.size(); i++) {
            result[updates[i][0]] += updates[i][2];
            if (updates[i][1] + 1 < length) {
                result[updates[i][1] + 1] -= updates[i][2];
            }
        }

        for (int i = 1; i < length; i++) {
            result[i] += result[i - 1];
        }
        return result;
    }
};
