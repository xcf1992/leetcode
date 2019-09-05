/*
154. Find Minimum in Rotated Sorted Array II
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

The array may contain duplicates.

Example 1:

Input: [1,3,5]
Output: 1
Example 2:

Input: [2,2,2,0,1]
Output: 0
Note:

This is a follow up problem to Find Minimum in Rotated Sorted Array.
Would allow duplicates affect the run-time complexity? How and why?
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
/*
When num[mid] == num[hi],
we couldn't sure the position of minimum in mid's left or right,
so just let upper bound reduce one.

This solution is great, but I'd like to point out one thing:
this solution guarantees to find the min value, but not necessarily the correct pivot index!
e.g. [1,1,1,1,2,1,1], in this case, lo = 0 in the end,
which is not the correct pivot index.
With this "bug", it may cause error if we use this directly in LC81 - Search in Rotated Sorted Array II
To fix this:
*/
class Solution {
public:
    int findMin(vector<int>& num) {
        int left = 0;
        int right = num.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (num[mid] > num[right]) {
                left = mid + 1;
            }
            else if (num[mid] < num[right]) {
                right = mid;
            }
            else { // when num[mid] and num[hi] are same, fixed
                if (right != 0 and num[right] >= num[right - 1]) {
                    right -= 1;
                }
                else {
                    return num[right];
                }
            }
        }
        return num[left];
    }
};
