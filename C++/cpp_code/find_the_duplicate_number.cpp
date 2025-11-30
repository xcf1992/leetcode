/*
287. Find the Duplicate Number
https://leetcode.com/problems/find-the-duplicate-number/

Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive),
prove that at least one duplicate number must exist.
Assume that there is only one duplicate number,
find the duplicate one.

Example 1:
Input: [1,3,4,2,2]
Output: 2

Example 2:
Input: [3,1,3,4,2]
Output: 3

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n2).
There is only one duplicate number in the array, but it could be repeated more than once.
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
k is the length before entering circle,
c is the length of circle
A is the point to enter circle

When fast and slow meets, let the distance moved by slow be X
Then X = 2X-X = n*c where n is an integer and n*c>=k

So the meeting point of fast and slow has a offset (n*c-k)%c to point A

To let slow reach point A we need slow to go another k points, so that (n*c-k+k)%c=0

When finder goes from start point to A, the distance is k, slow goes the same distance, and we get the entrance of the
circle.

The entrance of circle has more than one in-pointers,
this means at least two numbers at different indices in the array have same value,
the index of slow and finder is the duplicate number.
*/
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int fast = 0;
        int slow = 0;
        do {
            // we need to make fast, and slow to the same value at beginning, otherwise it won't work
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (fast != slow);

        fast = 0;
        while (fast != slow) {
            fast = nums[fast];
            slow = nums[slow];
        }
        return slow;
    }
};