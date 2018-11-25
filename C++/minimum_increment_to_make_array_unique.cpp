/*
 Given an array of integers A, a move consists of choosing any A[i], and incrementing it by 1.
 
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
        if (A.empty()) {
            return 0;
        }
        sort(A.begin(), A.end());
        int result = 0;
        int minNum = A[0];
        for (int i = 1; i < A.size(); i++) {
            if (A[i] <= minNum) {
                result += minNum + 1 - A[i];
                A[i] = minNum + 1;
            }
            minNum = A[i];
        }
        return result;
    }
};
