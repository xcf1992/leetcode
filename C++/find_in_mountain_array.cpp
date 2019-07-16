/*
1095. Find in Mountain Array
(This problem is an interactive problem.)

You may recall that an array A is a mountain array if and only if:

A.length >= 3
There exists some i with 0 < i < A.length - 1 such that:
A[0] < A[1] < ... A[i-1] < A[i]
A[i] > A[i+1] > ... > A[A.length - 1]
Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target.  If such an index doesn't exist, return -1.

You can't access the mountain array directly.  You may only access the array using a MountainArray interface:

MountainArray.get(k) returns the element of the array at index k (0-indexed).
MountainArray.length() returns the length of the array.
Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.



Example 1:

Input: array = [1,2,3,4,5,3,1], target = 3
Output: 2
Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.
Example 2:

Input: array = [0,1,2,4,2,1], target = 3
Output: -1
Explanation: 3 does not exist in the array, so we return -1.


Constraints:

3 <= mountain_arr.length() <= 10000
0 <= target <= 10^9
0 <= mountain_arr.get(index) <= 10^9
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

// This is the MountainArray's API interface.
// You should not implement it, or speculate about its implementation
class MountainArray {
public:
    int get(int index);
    int length();
};

/*
Intuition
Triple Binary Search, Triple Happiness.
Binary find peak in the mountain.
852. Peak Index in a Mountain Array
Binary find the target in strict increasing array
Binary find the target in strict decreasing array


Personally, (just a tip)
If I want find the index, I always use while (left < right)
If I may return the index during the search, I'll use while (left <= right)

Complexity
Time O(logN) Space O(1)

Some Improvement
Cache the result of get, in case we make the same calls.
In sacrifice of O(logN) space for the benefit of less calls.
Binary search of peak is unnecessary, just easy to write.
*/
class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        int left = 0;
        int right = n - 1;
        int peak = 0;

        // get the peak index
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;
                peak = left;
            }
            else {
                right = mid;
            }
        }

        // find in first part of increasing list
        left = 0;
        right = peak;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) == target) {
                return mid;
            }

            if (mountainArr.get(mid) < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        // find in second part of decreasing list
        left = peak;
        right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) == target) {
                return mid;
            }

            if (mountainArr.get(mid) < target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return -1;
    }
};
