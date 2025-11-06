/*
1562. Find Latest Group of Size M
https://leetcode.com/problems/find-latest-group-of-size-m/

Given an array arr that represents a permutation of numbers from 1 to n.
You have a binary string of size n that initially has all its bits set to zero.

At each step i (assuming both the binary string and arr are 1-indexed) from 1 to n,
the bit at position arr[i] is set to 1. You are given an integer m and
you need to find the latest step at which there exists a group of ones of length m.
A group of ones is a contiguous substring of 1s such that it cannot be extended in either direction.

Return the latest step at which there exists a group of ones of length exactly m.
If no such group exists, return -1.

Example 1:
Input: arr = [3,5,1,2,4], m = 1
Output: 4
Explanation:
Step 1: "00100", groups: ["1"]
Step 2: "00101", groups: ["1", "1"]
Step 3: "10101", groups: ["1", "1", "1"]
Step 4: "11101", groups: ["111", "1"]
Step 5: "11111", groups: ["11111"]
The latest step at which there exists a group of size 1 is step 4.

Example 2:
Input: arr = [3,1,5,4,2], m = 2
Output: -1
Explanation:
Step 1: "00100", groups: ["1"]
Step 2: "10100", groups: ["1", "1"]
Step 3: "10101", groups: ["1", "1", "1"]
Step 4: "10111", groups: ["1", "111"]
Step 5: "11111", groups: ["11111"]
No group of size 2 exists during any step.

Example 3:
Input: arr = [1], m = 1
Output: 1

Example 4:
Input: arr = [2,1], m = 2
Output: 2

Constraints:
n == arr.length
1 <= n <= 10^5
1 <= arr[i] <= n
All integers in arr are distinct.
1 <= m <= arr.length
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
#include <cfloat>
#include <stdio.h>
#include <map>
using namespace std;
/*
count[i] means the length of the group.
When we set bit a, where a = A[i],
we check the length of group on the right length[a - 1]
also the length of group on the right length[a - 1].
Then we update length[a], length[a - left], length[a + right] to left + right + 1.

Note that the length value is updated on the leftmost and the rightmost bit of the group.
The length value inside the group may be out dated.

As we do this, we also update the count of length.
If count[m] > 0, we update res to current step index i + 1.
*/
class Solution {
public:
    int findLatestStep(vector<int>& A, int m) {
        int res = -1, n = A.size();
        vector<int> length(n + 2), count(n + 1);
        for (int i = 0; i < n; ++i) {
            int a = A[i], left = length[a - 1], right = length[a + 1];
            length[a] = length[a - left] = length[a + right] = left + right + 1;
            count[left]--;
            count[right]--;
            count[length[a]]++;
            if (count[m])
                res = i + 1;
        }
        return res;
    }
};