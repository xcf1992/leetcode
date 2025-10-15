/*
1775. Equal Sum Arrays With Minimum Number of Operations
https://leetcode.com/problems/equal-sum-arrays-with-minimum-number-of-operations/

You are given two arrays of integers nums1 and nums2, possibly of different lengths.
The values in the arrays are between 1 and 6, inclusive.

In one operation, you can change any integer's value in any of the arrays to any value between 1 and 6, inclusive.

Return the minimum number of operations required to make the sum of values in nums1 equal to the sum of values in nums2.
Return -1​​​​​ if it is not possible to make the sum of the two arrays equal.

Example 1:
Input: nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
Output: 3
Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
- Change nums2[0] to 6. nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2].
- Change nums1[5] to 1. nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2].
- Change nums1[2] to 2. nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2].
Example 2:
Input: nums1 = [1,1,1,1,1,1,1], nums2 = [6]
Output: -1
Explanation: There is no way to decrease the sum of nums1 or to increase the sum of nums2 to make them equal.
Example 3:
Input: nums1 = [6,6], nums2 = [1]
Output: 3
Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
- Change nums1[0] to 2. nums1 = [2,6], nums2 = [1].
- Change nums1[1] to 2. nums1 = [2,2], nums2 = [1].
- Change nums2[0] to 4. nums1 = [2,2], nums2 = [4].

Constraints:
1 <= nums1.length, nums2.length <= 105
1 <= nums1[i], nums2[i] <= 6
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution
{
public:
    int minOperations(vector<int> &nums1, vector<int> &nums2)
    {
        int s1 = 0, s2 = 0;
        for (int &x : nums1)
            s1 += x;
        for (int &x : nums2)
            s2 += x;
        if (s1 > s2)
            swap(nums1, nums2), swap(s1, s2);

        // from here sum(nums1) <= sum(nums2) ie, s1 <= s2
        // now our task is to make both s1 and s2 equal by some good operations.
        // we have two ways to do that
        //      1. either increase some elements to '6' in nums1.
        //      2. decrease some elements to '1' in nums2.

        int ans = 0, diff = s2 - s1; // so,  we need to recover this 'diff'.
        if (diff == 0)
            return 0;

        vector<int> arr;
        for (int &x : nums1)
            arr.push_back(6 - x);
        // 6 - x signifies how much increment it does if we change a element 'x' to '6' in nums1 in one operation. ( 1st way )
        // this operation increases s1 by '6 - x', (diff = s2 - s1) (as s1 increases then diff decreases).

        for (int &x : nums2)
            arr.push_back(x - 1);
        // similarly, x - 1 signifies how much decrement it does if we change a element 'x' to '1' in nums2 in one operation. (2nd way)
        // this operation decreases s2 by 'x - 1', (diff = s2 - s1) (as s2 decreases then diff decreases).

        sort(arr.rbegin(), arr.rend());
        // sorting in desending order to pick the most valuable operation that decreases the 'diff'. (Yes, Greedy)

        for (int &x : arr)
        {
            ans++;
            diff -= x;
            if (diff <= 0)
                return ans; // at some operation may diff == 0
                            // if diff < 0 then we can adjust last operation to our needs.
        }
        return -1;
    }
    // follow up we can make this works in O(n) using count sort instead.
};
