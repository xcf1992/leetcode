/*
1133. Largest Unique Number
Given an array of integers A, return the largest integer that only occurs once.

If no integer occurs once, return -1.

Example 1:

Input: [5,7,3,9,4,9,8,3,1]
Output: 8
Explanation:
The maximum integer in the array is 9 but it is repeated. The number 8 occurs only once, so it's the answer.
Example 2:

Input: [9,9,8,8]
Output: -1
Explanation:
There is no number that occurs only once.


Note:

1 <= A.length <= 2000
0 <= A[i] <= 1000
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
    int largestUniqueNumber(vector<int>& A) {
        vector<int> count(1001, 0);
        for (int a : A) {
            count[a] += 1;
        }
        for (int i = 1000; i >= 0; --i) {
            if (count[i] == 1) {
                return i;
            }
        }
        return -1;
    }
};