/*
 977. Squares of a Sorted Array
 Given an array of integers A sorted in non-decreasing order,
 return an array of the squares of each number,
 also in sorted non-decreasing order.

 Example 1:

 Input: [-4,-1,0,3,10]
 Output: [0,1,9,16,100]
 Example 2:

 Input: [-7,-3,2,3,11]
 Output: [4,9,9,49,121]


 Note:

 1 <= A.length <= 10000
 -10000 <= A[i] <= 10000
 A is sorted in non-decreasing order.
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
    vector<int> sortedSquares(vector<int>& A) {
        int n = A.size();
        vector<int> result;
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            if (abs(A[left]) < abs(A[right])) {
                result.push_back(A[right] * A[right]);
                right -= 1;
            } else {
                result.push_back(A[left] * A[left]);
                left += 1;
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};