/*
378. Kth Smallest Element in a Sorted Matrix
https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/

Given a n x n matrix where each of the rows and columns are sorted in ascending order,
find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order,
not the kth distinct element.

Example:
matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,
return 13.

Note:
You may assume k is always valid, 1 ≤ k ≤ n2.
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
using namespace std;
/*
For those who don't understand why it's guaranteed to have lo as an element in the matrix, here is my two cents.

Basically, the method in the solution is a variation of binary search to "find the first occurrence of an element".

The count is the number of elements less or equal to mid, given the "matrix[i][j] > mid "in the while condition.
There are two scenarios:
Single Kth smallest element in matrix.
[1,2,3,5]
[2,3,5,7]
[3,5,8,9]
[5,8,9,13]
k = 11
Result = 7

This ensures count equals to k at a point,
in which it includes the kth smallest element in the matrix.
At the moment, binary search shrinks high boundary to mid,
instead of returning mid in the regular binary search.
You can imagine it as "hi" is waiting at the right spot for "lo" to meet him. (Like dating!)

Multiple Kth smallest element in matrix.
[1,2,3,5]
[2,3,5,7]
[3,7,8,9]
[7,8,9,13]
k = 9
Result = 7

Count won't be equal to k, but "hi" is still guaranteed to stop at right spot.
In the above example, the count is 11 when "mid" is 7.
After "hi" shrinks to mid, it will not move until "lo" comes to him.

To sum up, "lo" is ensured to reach an authentic element in the matrix,
because "hi" will approach and sit at the right spot anyway.
*/
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int left = matrix[0][0];
        int right = matrix[n - 1][n - 1];
        while (left < right) {
            int middle = left + (right - left) / 2;

            int smaller = 0;
            for (int i = 0; i < n; i++) {
                smaller += upper_bound(matrix[i].begin(), matrix[i].end(), middle) - matrix[i].begin();
            }

            if (smaller < k) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        return left;
    }
};