/*
334. Increasing Triplet Subsequence
https://leetcode.com/problems/increasing-triplet-subsequence/

Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.

Formally the function should:
Return true if there exists i, j, k
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.

Note:
Your algorithm should run in O(n) time complexity and O(1) space complexity.

Example 1:
Input: [1,2,3,4,5]
Output: true

Example 2:
Input: [5,4,3,2,1]
Output: false
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
The solution seems to fail for the input where the smallest element's index surpasses the second smallest one's.
Consider for example [2, 6, 1, 8]. c1 here would get updated to 1, c2 to 2 and 3rd element to 8.
Even though second largest and largest elements are correct,
the correct order of subsequence should be 2, 6, 8 and not 1, 6, 8(As reflected by the suggested code).
Even though this can be argued to suggest to form a subsequence by interchanging c1 and c2,
you might need to perform a Lil extra check for that

The question only asks whether it exists.
The key to prove this solution is always correct is that there is always a number before c2 that is less than c2,
which might or might not be c1 (otherwise, c2==INT_MAX and wont get updated).
Now if a number is greater than c2, we can safely return true.
*/
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int smallest = INT_MAX;
        int smaller = INT_MAX;
        for (int n : nums) {
            if (n <= smallest) {
                smallest = n;
            } else if (n <= smaller) {
                smaller = n;
            } else {
                return true;
            }
        }
        return false;
    }
};